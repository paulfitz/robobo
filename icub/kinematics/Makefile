BLENDER = /blender-2.5-alpha2-linux-glibc27-i686/blender

test.py: parse_ale.pl skeleton.ini kino.py DummyRobot.py Makefile
	./parse_ale.pl < skeleton.ini > test.py
	python test.py

blender.py: BlenderRobot.py test.py Makefile
	( echo "import bpy"; cat BlenderRobot.py kino.py test.py | grep -v "^import " | grep -v " import " | sed "s/robot = Robot/robot = BlenderRobot/") > blender.py

run: blender.py
	$(BLENDER) -b empty.blend -P blender.py

manual: blender.py
	# editmode stuff does not work from scripts, we have to go manual
	# type "import blender" from blender python console
	cp blender.py /tmp
	$(BLENDER) -w empty.blend -P setup.py

show:
	$(BLENDER) -w /tmp/test.blend

