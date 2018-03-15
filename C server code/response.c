#define MAXLINE 1024
#define IMAGE_DIR "images/"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>  // Used to inspect directory contents.
#include "response.h"
#include "request.h"

// Functions for internal use only.
void write_image_list(int fd);
void write_image_response_header(int fd);


/*
 * Write the main.html response to the given fd.
 * This response dynamically populates the image-filter form with
 * the filenames located in IMAGE_DIR.
 */
void main_html_response(int fd, char *filename1) {
    char *header =
        "HTTP/1.1 200 OK\r\n"
        "Content-type: text/html\r\n\r\n";

    if(write(fd, header, strlen(header)) == -1) {
        perror("write");
    }

    FILE *in_fp = fopen(filename1, "rb");
    int n1 = fileno(in_fp);
    int n;
    char buf[MAXLINE];
    while ((n = read(n1, buf, MAXLINE)) > 0) {
        if(write(fd, buf, n) < n) {
            perror("write");
        }
    }
    fclose(in_fp);
}

void main_css_response(int fd, char *filename1) {
    char *header =
        "HTTP/1.1 200 OK\r\n"
        "Content-type: text/css\r\n\r\n";

    if(write(fd, header, strlen(header)) == -1) {
        perror("write");
    }

    FILE *in_fp = fopen(filename1, "rb");
    int n1 = fileno(in_fp);
    int n;
    char buf[MAXLINE];
    while ((n = read(n1, buf, MAXLINE)) > 0) {
        if(write(fd, buf, n) < n) {
            perror("write");
        }
    }
    fclose(in_fp);
}

void main_js_response(int fd, char *filename1) {
    char *header =
        "HTTP/1.1 200 OK\r\n"
        "Content-type: application/javascript\r\n\r\n";

    if(write(fd, header, strlen(header)) == -1) {
        perror("write");
    }

    FILE *in_fp = fopen(filename1, "rb");
    int n1 = fileno(in_fp);
    int n;
    char buf[MAXLINE];
    while ((n = read(n1, buf, MAXLINE)) > 0) {
        if(write(fd, buf, n) < n) {
            perror("write");
        }
    }
    fclose(in_fp);
}

void main_img_response(int fd, char *filename1) {
    char *header =
        "HTTP/1.1 200 OK\r\n"
        "Content-type: image/jpeg\r\n\r\n";

    if(write(fd, header, strlen(header)) == -1) {
        perror("write");
    }

    FILE *in_fp = fopen(filename1, "rb");
    int n1 = fileno(in_fp);
    int n;
    char buf[MAXLINE];
    while ((n = read(n1, buf, MAXLINE)) > 0) {
        if(write(fd, buf, n) < n) {
            perror("write");
        }
    }
    fclose(in_fp);
}

void main_wav_response(int fd, char *filename1) {
    char *header =
        "HTTP/1.1 200 OK\r\n"
        "Content-type: audio/*\r\n\r\n";

    if(write(fd, header, strlen(header)) == -1) {
        perror("write");
    }

    FILE *in_fp = fopen(filename1, "rb");
    int n1 = fileno(in_fp);
    int n;
    char buf[MAXLINE];
    while ((n = read(n1, buf, MAXLINE)) > 0) {
        if(write(fd, buf, n) < n) {
            perror("write");
        }
    }
    fclose(in_fp);
}

/*
 * Write the header for a bitmap image response to the given fd.
 */
void write_image_response_header(int fd) {
    char *response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: image/bmp\r\n"
        "Content-Disposition: attachment; filename=\"output.bmp\"\r\n\r\n";

    write(fd, response, strlen(response));
}


void not_found_response(int fd) {
    char *response =
        "HTTP/1.1 404 Not Found\r\n"
        "Content-Type: text/plain\r\n\r\n"
        "Page not found.\r\n";
    write(fd, response, strlen(response));
}


void internal_server_error_response(int fd, const char *message) {
    char *response =
        "HTTP/1.1 500 Internal Server Error\r\n"
        "Content-Type: text/html\r\n\r\n"
        "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML 2.0//EN\">\r\n"
        "<html><head>\r\n"
        "<title>500 Internal Server Error</title>\r\n"
        "</head><body>\r\n"
        "<h1>Internal Server Error</h1>\r\n"
        "<p>%s<p>\r\n"
        "</body></html>\r\n";

    dprintf(fd, response, message);
}


void bad_request_response(int fd, const char *message) {
    char *response_header =
        "HTTP/1.1 400 Bad Request\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %d\r\n\r\n";
    char *response_body =
        "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML 2.0//EN\">\r\n"
        "<html><head>\r\n"
        "<title>400 Bad Request</title>\r\n"
        "</head><body>\r\n"
        "<h1>Bad Request</h1>\r\n"
        "<p>%s<p>\r\n"
        "</body></html>\r\n";
    char header_buf[MAXLINE];
    char body_buf[MAXLINE];
    sprintf(body_buf, response_body, message);
    sprintf(header_buf, response_header, strlen(body_buf));
    write(fd, header_buf, strlen(header_buf));
    write(fd, body_buf, strlen(body_buf));
    // Because we are making some simplfications with the HTTP protocol
    // the browser will get a "connection reset" message. This happens
    // because our server is closing the connection and terminating the process.
    // So this is really a hack.
    sleep(1);
}


void see_other_response(int fd, const char *other) {
    char *response =
        "HTTP/1.1 303 See Other\r\n"
        "Location: %s\r\n\r\n";

    dprintf(fd, response, other);
}
