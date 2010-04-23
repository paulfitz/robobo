class BlenderRobot:
    def __init__(self):
        try:
            bpy.context.scene.objects.unlink(bpy.data.objects.get('Cube'))
        except:
            pass
        try:
            army = bpy.data.objects.get('Armature')
            army.name = "OldArmature"
            bpy.context.scene.objects.unlink(army)
        except:
            pass


    def finish(self):
        print("SHUTTING DOWN")
        bpy.ops.wm.save_as_mainfile(filename = "test.blend",
                                    path = "/tmp/test.blend",
                                    directory = "/tmp",
                                    check_existing = False)

        print("SHUT DOWN")

    def addRoot(self,unit):
        print("Add root " + unit.name)
        bpy.ops.object.armature_add(enter_editmode=True)
        self.robot = bpy.data.objects['Armature']
        self.armature = self.robot.data
        self.armature.edit_bones.remove(self.armature.edit_bones[0])
        self.robot.location.x = 0;
        self.robot.location.y = 0;
        bpy.context.scene.update()
        
    def addJoint(self,unit,parent):
        print("Add joint " + unit.name + " with parent " + parent.name)
        bone = self.armature.edit_bones.new(unit.name)
        bone.local_location = True
        try:
            parent_bone = self.armature.edit_bones[parent.name]
            print("Parent found")
            bone.connected = True
            bone.length = 1
            bone.head = parent_bone.tail
            bone.tail = parent_bone.tail
            bone.tail.y += 1
            bone.parent = parent_bone
            bone.align_orientation(parent_bone)
        except:
            parent_bone = None
            bone.tail.y = 1
        bpy.context.scene.update()

    def addUnit(self,unit):
        if unit.parent == None:
            self.addRoot(unit)
            return
        self.addJoint(unit,unit.parent)
        
