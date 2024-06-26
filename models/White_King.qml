import QtQuick
import QtQuick3D

Node {
    id: node

    // Resources
    PrincipledMaterial {
        id: white_3D_Piece_material
        objectName: "White 3D Piece"
        baseColor: "#ffcccccc"
        roughness: 0.5
    }
    PrincipledMaterial {
        id: inside_White_material
        objectName: "Inside White"
        baseColor: "#ff0dcc0d"
        roughness: 0.4000000059604645
    }

    // Nodes:
    Node {
        id: rootNode
        objectName: "RootNode"
        rotation: Qt.quaternion(0.707107, -0.707107, 0, 0)
        Model {
            id: white_King
            objectName: "White_King"
            rotation: Qt.quaternion(1, 0, 0, 0)
            scale: Qt.vector3d(90.1646, 90.1646, 106.291)
            source: "meshes/white_King_mesh.mesh"
            materials: [
                white_3D_Piece_material,
                inside_White_material
            ]
        }
    }

    // Animations:
}
