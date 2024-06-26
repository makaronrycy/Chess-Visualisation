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
            id: white_Pawn
            objectName: "White_Pawn"
            scale: Qt.vector3d(110.738, 110.738, 100)
            source: "meshes/white_Pawn_mesh.mesh"
            materials: [
                white_3D_Piece_material,
                inside_White_material
            ]
        }
    }

    // Animations:
}
