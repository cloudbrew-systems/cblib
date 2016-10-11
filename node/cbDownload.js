var cbDownload = require("./cbDownload.node");

var downloadInfo = {
	TYPE: "PSV",
	UID : "1000",
	FN : "Cisco webex player.msi"
};

console.log("some work before");

/* Initialize the cbDownload node by calling "start_download" that triggers the method DownloadDataAsync() in cbDownload_wrapper.cpp*/
cbDownload.start_download(JSON.stringify(downloadInfo), function(downloadJSON) {
	console.log("downloadJSON is " + JSON.stringify(downloadJSON));
});

console.log("some work after");

