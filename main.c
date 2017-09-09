#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>

int main(int argc, char *argv[])
{
  virConnectPtr conn;
  conn = virConnectOpen("qemu:///system");
  if (conn == NULL) {
    fprintf(stderr, "Failed to open connection to qemu:///system\n");
    return 1;
  }

  int numDomains = virConnectNumOfDomains(conn);
  int *activeDomains;

  activeDomains = malloc(sizeof(int) * numDomains);
  numDomains = virConnectListDomains(conn, activeDomains, numDomains);

  printf("Active domain IDs:\n");
  for (int i = 0 ; i < numDomains ; i++) {
	  printf(" %d\n", activeDomains[i]);
  }
  free(activeDomains);

  printf ("%d",numDomains);
  virConnectClose(conn);
  return 0;
}
