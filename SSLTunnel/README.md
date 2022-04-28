#TLS Tunnel example
学习openssl 使用的例子。实现了tls隧道的建立，以及单向传输数据的流程。

证书创建：

openssl req -x509 -newkey rsa:4096 -nodes -keyout key.pem -out cert.pem -days 365