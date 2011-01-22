bl_addon_info = {
    "name": "Export xEngine mesh",
    "author": "moadib",
    "version": (0, 1),
    "blender": (2, 5, 6),
    "api": 32738,
    "location": "File > Export > xEngine Mesh",
    "description": "Export the mesh for use in xEngine",
    "warning": "",
    "wiki_url": "",
    "tracker_url": "",
    "category": "Import-Export"}

import os, mathutils, math, struct
import bpy

def export_mesh(operator, context, filepath="", apply_modifiers=True):
    
    def swap(vec):
        if len(vec) == 3:
            return mathutils.Vector( [vec.x, vec.z, -vec.y] )
        else:
            raise AttributeError
                        
    scene = context.scene  
    obj = context.object

    if not obj:
        raise Exception("Select object to export")
        
    if scene.objects.active:
        bpy.ops.object.mode_set(mode='OBJECT')
        
    mesh = obj.create_mesh(scene, apply_modifiers, 'PREVIEW')
    #mesh.select_by_number_vertices('TRIANGLES')
    #mesh.quads_convert_to_tris()
    
    file = open(filepath, "wb")
    # header
    file.write(struct.pack('4c', 'H','S','E','M'))
    # vertex buffer
    file.write(struct.pack('4c', 'F','U','B','V'))
    vcount = len(mesh.vertices)
    file.write(struct.pack('I', vcount))
    for vidx, v in enumerate(mesh.vertices):
        x,y,z = swap(v.co)
        nx,ny,nz = swap(v.normal)
        tx,ty = [0.0, 0.0]
        for layer in mesh.uv_textures:
            for fidx, uvface in enumerate(layer.data):
                    face = mesh.faces[fidx]
                    if vidx in face.vertices:
                            uv = uvface.uv[ list(face.vertices).index(vidx) ]
                            tx, ty = [uv[0], 1.0 - uv[1]]
                            break
        vertex = struct.pack('3f3f2f',
                             x, y, z,
                             nx, ny, nz,
                             tx, ty)                        
        file.write(vertex)
   
    submeshes = []
    indices = []
    for midx, mat in enumerate(obj.data.materials):
        start_index = len(indices)*3
        for F in mesh.faces:	#ob.data.faces:
                ## skip faces not in this material index ##
                if F.material_index != midx:
                    continue
                indices.append([F.vertices[0], F.vertices[1], F.vertices[2]])
                if len(F.vertices) == 4:
                    indices.append([F.vertices[0], F.vertices[2], F.vertices[3]])
        index_count = len(indices)*3 - start_index
        texture_name = ''
        for tex in mat.texture_slots:
            if tex and tex.texture.type == 'IMAGE':
                texture_name = os.path.basename(tex.texture.image.filepath)
                break
        submeshes.append([start_index, index_count, texture_name])
                                
    # index buffer
    file.write(struct.pack('4c', 'F','U','B','I'))
    short_indices = vcount <= 65535
    if short_indices:
        file.write(struct.pack('H', 0))
    else:
        file.write(struct.pack('H', 1))
    file.write(struct.pack('I', len(indices)*3))
    if short_indices:
        format = 'HHH'
    else:
        format = 'III'
    for i, tri in enumerate(indices):
        file.write(struct.pack(format, tri[0], tri[1], tri[2]))
    # submeshes
    file.write(struct.pack('4c', 'M','B','U','S'))
    file.write(struct.pack('I', len(submeshes)))
    for i, submesh in enumerate(submeshes):
        file.write(struct.pack('IIB', submesh[0], submesh[1], len(submesh[2])))
        file.write(submesh[2].encode('utf-8'))
    
    
    bpy.data.meshes.remove(mesh)    
    
    file.close()
    
    return {'FINISHED'}

from bpy.props import *
from io_utils import ExportHelper

class ExportMesh(bpy.types.Operator, ExportHelper):
    '''Export selection to xEngine mesh file format (.mesh)'''
    bl_idname = "export_xengine.mesh"
    bl_label = "Export"

    filename_ext = ".mesh"

    applyModifiers = BoolProperty(name="Apply Modifiers", description="Apply modifiers to mesh objects", default=True)


    def execute(self, context):
        import math
        from mathutils import Matrix
        if not self.filepath:
            raise Exception("filepath not set")
        
        path = self.filepath
        if not path.lower().endswith(".mesh"):
            path += ".x"            

        return export_mesh(self, context, path, self.applyModifiers)


def menu_export_xengine_mesh(self, context):
    import os
    default_path = os.path.splitext(bpy.data.filepath)[0] + ".mesh"
    self.layout.operator(ExportMesh.bl_idname, text="xEngine Mesh (.mesh)").filepath = default_path

def register():
    bpy.types.INFO_MT_file_export.append(menu_export_xengine_mesh)

def unregister():
    bpy.types.INFO_MT_file_export.remove(menu_export_xengine_mesh)

if __name__ == "__main__":
    register()
