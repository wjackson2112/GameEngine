#  // Copyright (c) 2026 William Jackson
#  // Licensed under the MIT License

from http.server import HTTPServer, SimpleHTTPRequestHandler, test
import sys


class MyHandler(SimpleHTTPRequestHandler):
    # def do_GET(self):
    #     self.send_response(200)
    #     self.send_header("Cross-Origin-Embedder-Policy", "require-corp")
    #     self.send_header("Cross-Origin-Opener-Policy", "same-origin")
    #     self.end_headers()

    def end_headers(self):
        self.send_header("Cross-Origin-Embedder-Policy", "require-corp")
        self.send_header("Cross-Origin-Opener-Policy", "same-origin")
        SimpleHTTPRequestHandler.end_headers(self)


if __name__ == '__main__':
    test(MyHandler, HTTPServer, port=int(sys.argv[1]) if len(sys.argv) > 1 else 8000)
