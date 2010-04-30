to_rad = 3.14159265/180.0
ident = mathutils.RotationMatrix(0,4,mathutils.Vector(1,0,0))

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
        self.armature.drawtype = 'STICK'
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
            bone.parent = parent_bone
        except:
            parent_bone = None
        bone.head = [0, 0, 0]
        bone.tail = [1, 0, 0]
        bone.hinge = True

        # Doing some testing, coordinates always seem to be global
        # (at least, not relative to parent bones)

        if unit.rpy_xyz!=None:
            enc = unit.rpy_xyz[0]
            yaw = unit.rpy_xyz[1]*to_rad
            pitch = unit.rpy_xyz[2]*to_rad
            roll = unit.rpy_xyz[3]*to_rad
            x = unit.rpy_xyz[4]
            y = unit.rpy_xyz[5]
            z = unit.rpy_xyz[6]
            rotmin = unit.rpy_xyz[7]*to_rad
            rotmax = unit.rpy_xyz[8]*to_rad
            unit.prerot = ident
            t = mathutils.TranslationMatrix(mathutils.Vector(x*self.scale,
                                                             y*self.scale,
                                                             z*self.scale))
            unit.shift = t
            t = mathutils.RotationMatrix(yaw,4,mathutils.Vector(0,0,1))
            t = mathutils.RotationMatrix(pitch,4,mathutils.Vector(0,1,0))*t
            t = mathutils.RotationMatrix(roll,4,mathutils.Vector(1,0,0))*t
            unit.postrot = t
        if unit.dh!=None:
            enc = unit.dh[0]
            a = unit.dh[1]
            d = unit.dh[2]
            alpha = unit.dh[3]*to_rad
            theta0 = unit.dh[4]*to_rad
            thetamin = unit.dh[5]*to_rad
            thetamax = unit.dh[6]*to_rad
            t = mathutils.RotationMatrix(theta0,4,mathutils.Vector(0,0,1))
            unit.prerot = t
            t = mathutils.TranslationMatrix(mathutils.Vector(a*self.scale,
                                                             0.0,
                                                             d*self.scale))
            unit.shift = t
            t = mathutils.RotationMatrix(alpha,4,mathutils.Vector(1,0,0))
            unit.postrot = t
        #if bone.parent:
        #    bone.translate(bone.parent.tail) 
        #    bone.connected = True
        #bpy.context.scene.update()
        if parent!=None:
            t = parent.transform
        else:
            t = ident
        base = t
        #dt = mathutils.TranslationMatrix(t.translation_part())
        #dt_neg = mathutils.TranslationMatrix(t.translation_part().negate())
        #t = dt*unit.prerot*dt_neg*t
        t = unit.prerot*t
        t = unit.shift*t
        #dt = mathutils.TranslationMatrix(t.translation_part())
        #dt_neg = mathutils.TranslationMatrix(t.translation_part().negate())
        #t = dt*unit.postrot*dt_neg*t
        t = unit.postrot*t
        unit.transform = t
        bone.head = base*mathutils.Vector(0,0,0)
        bone.tail = unit.transform*mathutils.Vector(0,0,0)
        print("  " + str(bone.head))
        if (bone.tail-bone.head).length<0.01:
            bone.tail.x = bone.tail.x + 0.001
        bone.connected = True

    def addUnit(self,unit):
        unit.transform = ident
        unit.prerot = ident
        unit.shift = ident
        unit.postrot = ident
        if unit.parent == None:
            self.addRoot(unit)
            return
        self.addJoint(unit,unit.parent)
        
