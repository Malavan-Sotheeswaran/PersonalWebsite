#ifndef RESPONSE_H_
#define RESPONSE_H_

#include <sys/socket.h>
#include "request.h"


/*
 * Write the main responses to the given fd.
 */
void main_html_response(int fd, char *filename1);
void main_css_response(int fd, char *filename1);
void main_img_response(int fd, char *filename1);
void main_wav_response(int fd, char *filename1);
void main_icon_response(int fd, char *filename1);



/*
 * The following are generic responses for different HTTP response codes;
 * we have provided these for you to use in various parts of the assignment.
 * Some of them can be customized with a message.
 */
void not_found_response(int fd);
void bad_request_response(int fd, const char *message);
void internal_server_error_response(int fd, const char *message);

// This one takes a resource name instead, and redirects the client
// to that resource.
void see_other_response(int fd, const char *other);

#endif /* RESPONSE_H_*/
