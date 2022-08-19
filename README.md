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
QMap<QByteArray, QByteArray> headers;
QString url = "http://example.com";
QString data = "{\"data\":\"test\"";
QString response = "";

headers.insert("Content-Type", "application/json");
headers.insert("Accept", "application/json");

response = request.post(url, data, headers);

// Example GET request
CWebrequest request;
QMap<QByteArray, QByteArray> headers;
QString url = "https://example.com";
QString response = "";

headers.insert("Accept", "application/json");

response = request.get(url, headers);
```

