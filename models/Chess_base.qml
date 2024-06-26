import QtQuick
import QtQuick3D

Node {
    id: node

    // Resources
    Texture {
        id: c__Users_maury_SynologyDrive_3D_texture_darkwood_jpg_texture
        objectName: "darkwood.jpg"
        generateMipmaps: true
        mipFilter: Texture.Linear
        source: "maps/darkwood.jpg"
    }
    PrincipledMaterial {
        id: wood_material
        objectName: "Wood"
        baseColor: "#ff000000"
        baseColorMap: c__Users_maury_SynologyDrive_3D_texture_darkwood_jpg_texture
        roughness: 0.8318182229995728
    }
    PrincipledMaterial {
        id: letters_material
        objectName: "Letters"
        baseColor: "#ffcccccc"
        roughness: 0.5
    }

    // Nodes:
    Node {
        id: rootNode
        objectName: "RootNode"
        rotation: Qt.quaternion(0.707107, -0.707107, 0, 0)
        Model {
            id: chess_base
            objectName: "chess_base"
            position: Qt.vector3d(0, 0, 6.20819)
            scale: Qt.vector3d(100, 100, 100)
            source: "meshes/chess_base_mesh.mesh"
            materials: [
                wood_material,
                letters_material
            ]
        }
    }

    // Animations:
}
