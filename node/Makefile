
NODE_UPLOAD = cbUpload.node
NODE_DOWNLOAD = cbDownload.node

binding:
	node-gyp configure build
	cp build/Release/$(NODE_UPLOAD) .
	cp build/Release/$(NODE_DOWNLOAD) .

clean:
	rm -Rf build
	rm -f $(NODE_UPLOAD)
	rm -f $(NODE_DOWNLOAD)

