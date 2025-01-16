#include <stdio.h>
#include <stdlib.h>

#define MAX_DATA_SIZE 100

typedef struct {
  char data[MAX_DATA_SIZE];
  int seq_num;
} data_frame;

void send_data_frame(data_frame *frame) {
  
  printf("Sending data frame %d\n", frame->seq_num);
}

int receive_ack_frame() {
  // Receive the acknowledgment frame over the network
  int ack_num;
  printf("Received acknowledgment frame %d\n", ack_num);
  return ack_num;
}

int main() {
  data_frame frame;
  frame.seq_num = 0;

  send_data_frame(&frame);

  int ack_num = receive_ack_frame();

  if (ack_num == frame.seq_num) {
    printf("Data frame received successfully\n");
  } else {
    // Otherwise, the data frame was not received successfully and must be retransmitted
    printf("Data frame not received successfully. Retransmitting...\n");
    send_data_frame(&frame);
  }

  return 0;
}