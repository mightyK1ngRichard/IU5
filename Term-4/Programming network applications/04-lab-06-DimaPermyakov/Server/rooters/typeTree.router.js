const Router = require('express').Router
const router = Router()
const typeTreeController = require('../controller/typeTree.controller')

router.post('/type-tree', typeTreeController.createTypeTree)
router.get('/type-tree', typeTreeController.getAllTypes)
router.get('/type-tree/:id', typeTreeController.getTypeById)
router.delete('/type-tree/:id', typeTreeController.deleteTypeTree)

module.exports = router
