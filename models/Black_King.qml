import QtQuick
import QtQuick3D

Node {
    id: node

    // Resources
    PrincipledMaterial {
        id: black_3D_Piece_material
        objectName: "Black 3D Piece"
        baseColor: "#ff050505"
        roughness: 0.5
    }
    PrincipledMaterial {
        id: inside_Black_material
        objectName: "Inside Black"
        baseColor: "#ffcc1512"
        roughness: 0.4000000059604645
    }

    // Nodes:
    Node {
        id: rootNode
        objectName: "RootNode"
        rotation: Qt.quaternion(0.707107, -0.707107, 0, 0)
        Model {
            id: black_King
            objectName: "Black_King"
            scale: Qt.vector3d(98.0379, 98.0379, 106.291)
            source: "meshes/black_King_mesh.mesh"
            materials: [
                black_3D_Piece_material,
                inside_Black_material
            ]
        }
    }

    // Animations:
}
