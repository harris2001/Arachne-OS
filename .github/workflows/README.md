# CI/CD Workflow

Using this GitHub Actions workflow, we can automatically build and test ArachneOS whenever code is pushed from a PR and check if there are any issues introduced. We are using the Dockerfile that sets up developers' environment for consistency.

## How it works 
1. Checks out the code (only on PRs to main)
2. Builds the Docker image from `devs/Dockerfile` with all our build tools
3. Compiles the kernel inside that container using `make all`
4. Verifies the build outputs exist (`kernel.bin` and the bootable ISO)
5. Tests booting in QEMU (runs for 10 seconds in headless mode)
6. Uploads the artifacts for users to download 

## Testing Locally

If you are a developer and want to submit a PR, you can verify your solution by running the same steps as the CI locally like this:

```bash
cd devs
docker build . -t dev-environment

cd ..
docker run --rm -v $(pwd):/root/env dev-environment make all
docker run --rm -v $(pwd):/root/env dev-environment make test-ci
```

## Downloading Builds

If the CI succeeds, it uploads the compiled kernel and ISO as artifacts for users to download from the Actions tab on Github (currrently only retained for 30 days).