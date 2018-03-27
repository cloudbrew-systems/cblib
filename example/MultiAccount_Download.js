var cbDownload = require("../node/cbDownload.node");

var downloadInfo = {
	TYPE: "PSV",
	SPLT : "Y",
	ENC : "Y",
	UID : "57935cc35d664a7a13dc78dc",
	FN : "dev-guide.pdf"
};

/* Initialize the cbDownload node by calling "start_download" that triggers the method DownloadDataAsync() in cbDownload_wrapper.cpp */
cbDownload.start_download(JSON.stringify(downloadInfo), function(downloadJSON) {
	console.log("downloadJSON is " + JSON.stringify(downloadJSON));
});
