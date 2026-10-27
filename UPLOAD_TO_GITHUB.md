# Upload and deploy

1. Extract the ZIP. Open the extracted folder.
2. Upload its CONTENTS to the top level of Moo202020/embedded-iot-profolio. Do not upload the ZIP itself or add an extra parent folder.
3. Confirm wrangler.jsonc, README.md, public/ and projects/ appear together at the repository root. Keep the existing .github workflow.
4. Commit to main.
5. In your existing Cloudflare Worker, use repository root /, leave the build command empty and keep the deploy command: npx wrangler deploy
6. Retry deployment, or let the commit trigger it.

The public folder contains the website and its photo. Firmware and documentation stay in their existing folders. This website needs no database, API key or npm build step.
