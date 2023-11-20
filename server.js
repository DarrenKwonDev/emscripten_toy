const express = require("express");

const app = express();
const PORT = 30012;

app.use(
    express.static("public", {
        setHeaders: (res, path, stat) => {
            if (path.endsWith(".wasm")) {
                res.set("Content-Type", "application/wasm");
            }
        },
    })
);

app.listen(PORT, () => {
    console.log("http://localhost:" + PORT);
});
