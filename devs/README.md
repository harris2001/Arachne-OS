# Developer Guide
This document provides a quick overview of how to set up and contribute to the project as a developer.
## Setup
Make sure that you have docker installed and then simply run (from the current directory):
```bash
docker build . -t dev-environment
docker run --rm -it -v $(pwd)/..:/root/env dev-environment
```
