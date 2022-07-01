# qt_web_request_in_cpp


```
QT += network
```

## Requirements

.pro file
```
QT += network

LIBS += {open_ssl_path}\libcrypto.lib
LIBS += {open_ssl_path}\libssl.lib
```

## Example
```
// Example POST request
CWebrequest request;
QMap<QByteArray, QByteArray> options;
QString url = "http://example.com";
QString data = "{\"data\":\"test\"";
QString response = "";

options.insert("Content-Type", "application/json");
options.insert("Accept", "application/json");

response = request.post(url, data, options);

// Example GET request
CWebrequest request;
QMap<QByteArray, QByteArray> options;
QString url = "https://google.com";
QString response = "";

options.insert("Accept", "application/json");

response = request.posgett(url, options);
```

