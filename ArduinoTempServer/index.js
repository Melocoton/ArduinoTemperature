const express = require('express');
const cors = require('cors');
const bodyParser = require('body-parser');
const fs = require('fs');
const { strict } = require('assert');

const port = 9001;

let clients = [];

const app = express();

app.use(cors())
app.use(bodyParser.json())
app.use(bodyParser.urlencoded({ extended: true }));

app.post('/temp', (req, res) => {
    console.log(Date());
    console.log(req.body);

    res.sendStatus(200);
});

app.listen(port, () => {
    console.log(`Server started in port: ${port}`);
});

