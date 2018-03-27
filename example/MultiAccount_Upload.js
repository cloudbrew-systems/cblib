var cbUpload = require("../node/cbUpload.node");

var uploadInfo = {
	TYPE: "PSV",
	SPLT : "Y",
	ENC : "Y",
	UID : "57935cc35d664a7a13dc78dc",
	FN : "dev-guide.pdf",
	FAL : "sample_files/dev-guide.pdf",
	ACS : [
		{ "AN" : "Dropbox#1_57935cc35d664a7a13dc78dc", "TS" : 6368709124, "US" : 5121223751, "MFS": 0 },
		{ "AN" : "OneDrive#1_57935cc35d664a7a13dc78dc", "TS" : 7737418240, "US" : 3368709120, "MFS": 0 },
		{ "AN" : "OneDrive#2_57935cc35d664a7a13dc78dc", "TS" : 10737418240, "US" : 5368709120, "MFS": 0 },
		{ "AN" : "GoogleDrive#1_57935cc35d664a7a13dc78dc", "TS" : 1521225472, "US" : 1068709120, "MFS": 25102789 },
		{ "AN" : "Box#1_57935cc35d664a7a13dc78dc", "TS" : 3221225472, "US" : 1368709120, "MFS": 25102789 },
		{ "AN" : "Box#2_57935cc35d664a7a13dc78dc", "TS" : 8221225356, "US" : 7268709120, "MFS": 25102789 },
		{ "AN" : "GoogleDrive#3_57935cc35d664a7a13dc78dc", "TS" : 16106127360, "US" : 4032228790, "MFS": 524288000 },
		{ "AN" : "Dropbox#2_57935cc35d664a7a13dc78dc", "TS" : 5368709120, "US" : 3221225472, "MFS": 0 },
		{ "AN" : "GoogleDrive#2_57935cc35d664a7a13dc78dc", "TS" : 3221225472, "US" : 1368709120, "MFS": 25102789 },
		{ "AN" : "Dropbox#3_57935cc35d664a7a13dc78dc", "TS" : 4368709120, "US" : 1221225472, "MFS": 0 },
		{ "AN" : "Box#3_57935cc35d664a7a13dc78dc", "TS" : 8221225356, "US" : 3268709120, "MFS": 5002789 },
		{ "AN" : "OneDrive#3_57935cc35d664a7a13dc78dc", "TS" : 5137418240, "US" : 1368724678, "MFS": 0 }
	]
};

/* Initialize the cbUpload node by calling "start_upload" that triggers the method UploadDataAsync() in cbUpload_wrapper.cpp */
cbUpload.start_upload(JSON.stringify(uploadInfo), function(uploadJSON) {
	console.log("uploadJSON is " + JSON.stringify(uploadJSON));
});
