const express = require('express')
const PORT = 8010
const HOST = 'localhost'
const typeTreeRouter = require('./rooters/typeTree.router')
const app = express()

app.use((req, res, next) => {
    res.setHeader('Access-Control-Allow-Origin', '*');
    res.setHeader('Access-Control-Allow-Methods', 'GET, POST, PUT, DELETE');
    res.setHeader('Access-Control-Allow-Headers', 'Content-Type');
    next();
});

app.use(express.json())
app.use('/wood', typeTreeRouter)


app.listen(PORT, HOST, () => {
    console.log(`Сервер запущен по адресу  http://${HOST}:${PORT}`);
});