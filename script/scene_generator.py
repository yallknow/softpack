import json
import random

WORLD_WIDTH = 6400.0
WORLD_HEIGHT = 3600.0

ENTITIES_COUNT = 50


def random_color():
    return {
        "red": random.randint(0, 255),
        "green": random.randint(0, 255),
        "blue": random.randint(0, 255)
    }


def random_body():
    return {
        "type": 2,
        "linearDamping": random.uniform(1.0, 3.0),
        "angularDamping": random.uniform(1.0, 3.0),
        "density": random.uniform(0.5, 1.5),
        "friction": random.uniform(0.5, 1.5),
        "restitution": random.uniform(0.5, 1.5)
    }


def random_brain():
    return {
        "type": 1,
        "velocity": {
            "x": random.uniform(-1500.0, 1500.0),
            "y": random.uniform(-15000.0, 15000.0)
        },
        "maxVelocity": {
            "x": random.uniform(100000.0, 150000.0),
            "y": random.uniform(100000.0, 150000.0)
        },
        "jitterStep": random.uniform(1000.0, 10000.0)
    }


def make_circle():
    return {
        "shape": {
            "type": "circle",
            "radius": random.uniform(50.0, 300.0),
            "position": {
                "x": random.uniform(100.0, WORLD_WIDTH - 600.0),
                "y": random.uniform(100.0, WORLD_HEIGHT - 600.0)
            },
            "color": random_color()
        },
        "body": random_body(),
        "brain": random_brain()
    }


def make_rectangle():
    return {
        "shape": {
            "type": "rectangle",
            "size": {
                "x": random.uniform(50.0, 300.0),
                "y": random.uniform(50.0, 300.0)
            },
            "position": {
                "x": random.uniform(50.0, WORLD_WIDTH - 300.0),
                "y": random.uniform(50.0, WORLD_HEIGHT - 300.0)
            },
            "color": random_color()
        },
        "body": random_body(),
        "brain": random_brain()
    }


def make_obstacle():
    return {
        "shape": {
            "type": "rectangle",
            "size": {
                "x": random.uniform(10.0, 100.0),
                "y": random.uniform(10.0, 100.0)
            },
            "position": {
                "x": random.uniform(100.0, WORLD_WIDTH - 100.0),
                "y": random.uniform(100.0, WORLD_HEIGHT - 100.0)
            },
            "color": random_color()
        },
        "body": random_body(),
        "brain": {
            "type": 0
        }
    }


def make_wall(x, y, w, h):
    return {
        "shape": {
            "type": "rectangle",
            "size": {"x": w, "y": h},
            "position": {"x": x, "y": y}
        },
        "body": {"type": 0},
        "brain": {"type": 0}
    }


def main():
    entities = []

    for _ in range(ENTITIES_COUNT):
        value = random.random()
        if value < 0.33:
            entities.append(make_circle())
        elif value < 0.66:
            entities.append(make_rectangle())
        else:
            entities.append(make_obstacle())

    entities.append(make_wall(WORLD_WIDTH * 0.5, 0.0, WORLD_WIDTH, 10.0))
    entities.append(make_wall(WORLD_WIDTH * 0.5,
                    WORLD_HEIGHT, WORLD_WIDTH, 10.0))
    entities.append(make_wall(0.0, WORLD_HEIGHT * 0.5, 10.0, WORLD_HEIGHT))
    entities.append(
        make_wall(WORLD_WIDTH, WORLD_HEIGHT * 0.5, 10.0, WORLD_HEIGHT))

    scene = {"entities": entities}

    with open("scene.json", "w") as f:
        json.dump(scene, f, indent=4)

    print("scene.json generated with", len(entities), "entities")


if __name__ == "__main__":
    main()
