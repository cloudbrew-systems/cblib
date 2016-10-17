var cbUpload = require("../node/cbUpload.node");

var uploadInfo = {
	TYPE : "PSV",
	SPLT : "Y",
	ENC : "Y",
	UID : "57935cc35d664a7a13dc78dc",
	FN : "dev-guide.pdf",
	FAL : "sample_files/dev-guide.pdf",
	ACS : [
		{ "AN" : "Dropbox#1_57935cc35d664a7a13dc78dc", "TS" : 6368709124, "US" : 5121223751, "MFS": 0 }
	]
};

/* Initialize the cbUpload node by calling "start_upload" that triggers the method UploadDataAsync() in cbUpload_wrapper.cpp*/
cbUpload.start_upload(JSON.stringify(uploadInfo), function(uploadJSON) {
	console.log("uploadJSON is " + JSON.stringify(uploadJSON));
});
