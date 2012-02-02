#BLENDER = /blender-2.5-alpha2-linux-glibc27-i686/blender
BLENDER = /opt/blender/blender-2.54-beta-linux-glibc27-x86_64/blender

test.py: parse_ale.pl skeleton.ini kino.py DummyRobot.py Makefile
	./parse_ale.pl < skeleton.ini > test.py
	python test.py

bvh.py: parse_ale.pl skeleton.ini kino.py BvhRobot.py Makefile
	./parse_ale.pl < skeleton.ini > bvh.py
	cp kino.py kino_bvh.py
	sed -i "s/DummyRobot/BvhRobot/g" kino_bvh.py
	sed -i "s/kino/kino_bvh/" bvh.py
	python bvh.py | tee /tmp/test.bvh

blender.py: BlenderRobot.py test.py Makefile
	( echo "import bpy"; echo "import Mathutils as mathutils"; cat BlenderRobot.py kino.py test.py | grep -v "^import " | grep -v " import " | sed "s/robot = Robot/robot = BlenderRobot/") > blender.py

run: blender.py
	$(BLENDER) -b empty.blend -P blender.py

manual: blender.py
	# editmode stuff does not work from scripts, we have to go manual
	# type "import blender" from blender python console
	cp blender.py /tmp
	$(BLENDER) -w empty.blend -P setup.py

show:
	$(BLENDER) -w /tmp/test.blend


play:
	$(BLENDER) -w play.blend -P play.py

blender:
	$(BLENDER)