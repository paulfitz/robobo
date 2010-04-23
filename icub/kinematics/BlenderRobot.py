class BlenderRobot:
    def __init__(self):
        self.scale = 0.01
        
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
            #bone.length = 1
            #bone.head = parent_bone.tail
            #bone.tail = parent_bone.tail
            #bone.tail.y += 1
            bone.parent = parent_bone
            #bone.align_orientation(parent_bone)
        except:
            parent_bone = None
            #bone.tail.y = 1
        bone.head = [0, 0, 0]
        bone.tail = [1, 0, 0]
        bone.hinge = True
        if bone.parent:
            bone.transform(bone.parent.matrix)

        unit.rpy_xyz = None
        #unit.dh = None
        to_rad = 3.14159265/180.0
        if unit.rpy_xyz!=None:
            enc = unit.rpy_xyz[0]
            yaw = unit.rpy_xyz[1]*to_rad
            pitch = unit.rpy_xyz[2]*to_rad
            roll = unit.rpy_xyz[3]*to_rad
            x = unit.rpy_xyz[4]
            y = unit.rpy_xyz[5]
            z = unit.rpy_xyz[6]
            rotmin = unit.rpy_xyz[7]
            rotmax = unit.rpy_xyz[8]
            bone.tail.x = x*self.scale
            bone.tail.y = y*self.scale
            bone.tail.z = z*self.scale
            rot = mathutils.Euler(yaw,pitch,roll)
            rot.order = 'XYZ'
            bone.transform(rot.to_matrix())
        if unit.dh!=None:
            enc = unit.dh[0]
            a = unit.dh[1]
            d = unit.dh[2]
            alpha = unit.dh[3]
            theta0 = unit.dh[4]
            thetamin = unit.dh[5]
            thetamax = unit.dh[6]
            bone.transform(mathutils.Euler(0,0,theta0).to_matrix())
            bone.tail.x = a*self.scale
            bone.tail.y = 0
            bone.tail.z = d*self.scale
            bone.transform(mathutils.Euler(alpha,0,0).to_matrix())
        if bone.parent:
            bone.translate(bone.parent.tail) 
            bone.connected = True
        #bpy.context.scene.update()

    def addUnit(self,unit):
        if unit.parent == None:
            self.addRoot(unit)
            return
        self.addJoint(unit,unit.parent)
        
