const db = require('../Database/woodDB')

class TypeTreeController {
    async createTypeTree(req, res) {
        const {name, photoURL, notes} = req.body
        const newType = await db.query(`
        INSERT INTO type_tree (name_type, photo, notes) VALUES ($1, $2, $3) RETURNING *;`, [name, photoURL, notes])
        res.json(newType.rows)
    }

    async getAllTypes(req, res) {
        const allTypes = await db.query(`
        SELECT t.name_type, t.notes, t.type_id, f.name as fertilizer_name, p.name_plot as plot_name, t.photo, COUNT(tree_id) as count_trees
        FROM tree
        FULL JOIN type_tree t ON tree.type_tree_id = t.type_id
        LEFT JOIN fertilizer f ON t.type_id = f.type_tree_id
        LEFT JOIN plot p on t.type_id = p.type_tree_id
        GROUP BY t.name_type, t.notes, t.type_id, f.name, p.name_plot;
        `)
        res.json(allTypes.rows)
    }

    async getTypeById(req, res) {
        const id = req.params.id
        const typeTree = await db.query(`
        SELECT t.name_type, t.notes, t.type_id, f.name as fertilizer_name, p.name_plot as plot_name, t.photo, COUNT(tree_id) as count_trees
        FROM tree
        FULL JOIN type_tree t ON tree.type_tree_id = t.type_id
        LEFT JOIN fertilizer f ON t.type_id = f.type_tree_id
        LEFT JOIN plot p on t.type_id = p.type_tree_id
        WHERE t.type_id=$1
        GROUP BY t.name_type, t.notes, t.type_id, f.name, p.name_plot;
        `, [id])
        res.json(typeTree.rows[0])
    }

    async deleteTypeTree(req, res) {
        const id = req.params.id
        const deletedType = await db.query(`DELETE FROM type_tree WHERE type_id = $1 RETURNING *;`, [id])
        res.json(deletedType.rows[0])
    }
}

module.exports = new TypeTreeController()