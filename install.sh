sudo mkdir /usr/include/agl/forms
sudo cp -Rap *.h /usr/include/agl/forms/
make release
sudo cp -Rap ../lib/*.so /usr/lib/
