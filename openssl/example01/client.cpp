#include <openssl/ssl.h>
#include <openssl/err.h>

using namespace std;

int SSL_verify_cb(int preverify_ok, X509_STORE_CTX *x509_ctx) 
{

}

int main(int argc, char** argv)
{
    SSL_library_init();
    SSL_load_error_strings();

    // 申请 SSL 会话环境
    SSL_CTX *ctx = SSL_CTX_new(TLSv1_2_method());

    // 指定证书验证方式
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, SSL_verify_cb);


    // 加载指定的CA 证书
    SSL_CTX_load_verify_locations(ctx, "ca.pem", NULL);

    // 从指定文件中加载 CA 证书
    SSL_load_client_CA_file("./Ca.pem");





    return EXIT_SUCCESS;
}