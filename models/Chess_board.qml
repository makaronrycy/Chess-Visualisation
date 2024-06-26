import QtQuick
import QtQuick3D

Node {
    id: node

    // Resources
    PrincipledMaterial {
        id: material_002_material
        objectName: "Material.002"
        baseColor: "#ff0f2005"
        roughness: 0.5
    }
    PrincipledMaterial {
        id: material_003_material
        objectName: "Material.003"
        baseColor: "#ff989342"
        roughness: 0.5
    }

    // Nodes:
    Node {
        id: rootNode
        objectName: "RootNode"
        rotation: Qt.quaternion(0.707107, -0.707107, 0, 0)
        Model {
            id: chess_board
            objectName: "chess_board"
            scale: Qt.vector3d(100, 100, 100)
            source: "meshes/chess_board_mesh.mesh"
            materials: [
                material_002_material,
                material_003_material
            ]
        }
    }

    // Animations:
}
