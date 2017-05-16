# Makefile

# Build the AGL library
release: form.cpp formcomponent.cpp button.cpp textfield.cpp
	g++ -fPIC -c form.cpp
	g++ -fPIC -c formcomponent.cpp
	g++ -fPIC -c button.cpp
	g++ -fPIC -c textfield.cpp
	g++ -shared -o ../lib/libagl-forms.so form.o formcomponent.o button.o textfield.o -lSDL -lagl -lagl-graphics -lagl-text

# Build the AGL library for debugging
debug: form.cpp formcomponent.cpp button.cpp textfield.cpp
	g++ -fPIC -g -c form.cpp
	g++ -fPIC -g -c formcomponent.cpp
	g++ -fPIC -g -c button.cpp
	g++ -fPIC -g -c textfield.cpp
	g++ -shared -g -o ../lib/libagl-forms.so form.o formcomponent.o button.o textfield.o -lSDL -lagl -lagl-graphics -lagl-text

# Build the test application
test: test.cpp
	g++ -g -fpermissive -o test test.cpp -lagl -lagl-text ../lib/libagl-forms.so

# Install the AGL library (debug) on the system
install_debug:
	../install_debug.sh

# Install the AGL library on the system
install:
	../install.sh

# Uninstall the AGL library to the system
remove:
	../remove.sh

# Generates the AGL documentation
doc:
	doxygen doxyfile

# Cleans the directories, removing executables and objects
clean:
	rm *.o test ../lib/*.so
