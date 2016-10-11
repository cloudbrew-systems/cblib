var cbUpload = require("./cbUpload.node");

var uploadInfo = {
	TYPE: "PSV",
	UID : "57935cc35d664a7a13dc78dc",
	FN : "Cisco webex player.msi",
	FAL : "../sample_files/Cisco webex player.msi",
	ACS : [
		{ "AN" : "GoogleDrive_57935cc35d664a7a13dc78dc", "TS" : 16106127360, "US" : 6442450944, "MFS": 0 },
		//{ "AN" : "OneDrive_User1", "TS" : 5368709120, "US" : 3221225472, "MFS": 0 },
		{ "AN" : "Dropbox_57935cc35d664a7a13dc78dc", "TS" : 10737418240, "US" : 5368709120, "MFS": 2510234 }
	]
};

console.log("some work before");

/* Initialize the cbUpload node by calling "start_upload" that triggers the method UploadDataAsync() in cbUpload_wrapper.cpp*/
cbUpload.start_upload(JSON.stringify(uploadInfo), function(uploadJSON) {
	console.log("uploadJSON is " + JSON.stringify(uploadJSON));
});

console.log("some work after");

