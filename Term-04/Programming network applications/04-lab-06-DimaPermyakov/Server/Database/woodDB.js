const Pool = require('pg').Pool
const {postgresPort} = require('../config')

const pool = new Pool({
    user: postgresPort.user_pg,
    host: postgresPort.host_pg,
    database: postgresPort.db_name_pg,
    password: postgresPort.password_pg,
    port: postgresPort.port_pg,
})

module.exports = pool