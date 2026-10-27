# Upload this portfolio

1. Extract the ZIP on your computer.
2. On GitHub create a repository named `embedded-iot-portfolio`. Start private while reviewing shared coursework permissions and hardware status.
3. Choose **uploading an existing file** (or **Add file → Upload files**).
4. Upload the contents inside `embedded-iot-portfolio`, so README.md is at the repository root. Do not upload the ZIP itself.
5. Browser uploads may skip hidden folders. To include `.github/workflows/host-tests.yml` and `.gitignore`, use GitHub Desktop or the command line.
6. Read the provenance notes and run the hardware checks before publishing. Pin the repository to your profile once you are happy with it.

Optional command line, run from the extracted repository folder:

```sh
git init
git add .
git status
git commit -m "Add embedded and IoT portfolio with source provenance and host tests"
git branch -M main
git remote add origin https://github.com/Moo202020/embedded-iot-portfolio.git
git push -u origin main
```

Do not initialise the GitHub repository with a separate README if using these commands. You will need Git authentication. Nothing in this package publishes automatically.

Suggested description: `Embedded C++ and IoT projects with Arduino, ESP32, sensors, MQTT and host-tested application logic.`
Suggested topics: `embedded`, `cpp`, `esp32`, `arduino`, `mqtt`, `iot`, `sensors`.
