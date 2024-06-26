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
            id: white_Rook
            objectName: "White_Rook"
            scale: Qt.vector3d(97.5318, 97.5318, 100)
            source: "meshes/white_Rook_mesh.mesh"
            materials: [
                white_3D_Piece_material,
                inside_White_material
            ]
        }
    }

    // Animations:
}
