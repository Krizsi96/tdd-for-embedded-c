import docker
from pathlib import Path
import requests
import logging

CONTAINER_NAME = "dev_container"
IMAGE_NAME = "tddec"

CLIENT = docker.DockerClient()


def main():
    logging.basicConfig(level=logging.INFO, format="%(message)s")

    try:
        project_dir = set_project_dir()
    except FileNotFoundError as e:
        logging.error(f"\n{e}")
        exit(1)

    CLIENT = set_up_docker_client()

    build_image(project_dir, IMAGE_NAME)

    try:
        container = start_dev_container(IMAGE_NAME, project_dir)
    except Exception as e:
        logging.error(f"\n{e}")
        exit(1)


def set_project_dir():
    project_dir = Path.cwd()
    logging.debug(f"project_dir: {project_dir}")

    if not (project_dir / "Dockerfile").exists():
        raise FileNotFoundError("Dockerfile not found in the project directory.")

    return project_dir


def set_up_docker_client() -> docker.DockerClient:
    logging.info("setting up the docker client...")
    client = docker.from_env()
    logging.debug(f"client: {client}")
    return client


def build_image(project_dir: Path, tag: str):
    logging.info("Building the image...")
    CLIENT.images.build(path=project_dir.as_posix(), tag=tag, quiet=False, timeout=600)
    logging.info(f"Image '{IMAGE_NAME}' is ready!")


def start_dev_container(
    image: str, volumes: Path
) -> docker.models.containers.Container:
    try:
        logging.info("Starting the container...")
        container = CLIENT.containers.run(
            image,
            "/bin/bash",
            detach=True,
            tty=True,
            stdin_open=True,
            name=CONTAINER_NAME,
            volumes={volumes: {"bind": "/data", "mode": "rw"}},
        )
        logging.info(f"{container.name} is ready!")
        return container
    except requests.exceptions.HTTPError as e:
        error_message = ""
        if e.response.status_code == 409:
            error_message = f"\nA container with the name '{CONTAINER_NAME}' already exists. Please remove it before trying again."
        if e.response.status_code == 404:
            error_message = f"\nImage '{IMAGE_NAME}' not found."
        raise Exception(error_message)


if __name__ == "__main__":
    main()
