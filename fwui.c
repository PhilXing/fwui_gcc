#include    <stdlib.h>
#include    <stdio.h>
#include    <fcntl.h>

#include    <sys/types.h>
#include    <efivar/efivar.h>

#define gEfiGlobalVariableGuid EFI_GUID(0x8BE4DF61, 0x93CA, 0x11D2, 0xAA0D, 0x00, 0xE0, 0x98, 0x03, 0x2B, 0x8C)
#define EFI_OS_INDICATIONS_BOOT_TO_FW_UI	0x0000000000000001

void ShowUsage(void)
{
  printf("This tool show file checksum by DWORD.\n\n"
    "Usage:  Checksum [Dest File] \n"
   "\n");
}

int main(int argc, char *argv[])
{

  efi_guid_t guid=gEfiGlobalVariableGuid;
  const char *name="OsIndicationsSupported";
  const char *name2="OsIndications";
  uint64_t data[1];
  uint64_t OsIndicationsSupported, OsIndications;
  size_t data_size=sizeof(OsIndicationsSupported);
  uint32_t attributes;
  
  if (!efi_variables_supported()) {
    printf("This is not an UEFI OS.\n");
    return -1;
  }
  efi_get_variable(gEfiGlobalVariableGuid, name, &data, &data_size, &attributes);
  OsIndicationsSupported = data[0] & 0xff;
  printf("%s\n", name);
  printf("%x\n", OsIndicationsSupported);
  printf("%x\n", data_size);
  printf("%x\n", attributes);

  // if ((OsIndicationsSupported & EFI_OS_INDICATIONS_BOOT_TO_FW_UI) == 0) {
  //     printf("Boot To FW UI is not supported by the system firmware.\n");
  //     return -2;
  // }

// extern int efi_get_variable(efi_guid_t guid, const char *name, uint8_t **data,
// 			    size_t *data_size, uint32_t *attributes)
// 				__attribute__((__nonnull__ (2, 3, 4, 5)));
  efi_get_variable(gEfiGlobalVariableGuid, name2, &data, &data_size, &attributes);
  OsIndications = data[0] & 0xff;
  printf("%s\n", name2);
  printf("%x\n", OsIndications);
  printf("%x\n", data_size);
  printf("%x\n", attributes);

  OsIndications |= EFI_OS_INDICATIONS_BOOT_TO_FW_UI;
  printf("\n%x\n\n", OsIndications);
// extern int efi_set_variable(efi_guid_t guid, const char *name, uint8_t *data, 
//           size_t data_size,  uint32_t attributes, mode_t mode)
  efi_set_variable(gEfiGlobalVariableGuid, name2, (uint8_t *)&OsIndications, &data_size, &attributes, 0xff);

  efi_get_variable(gEfiGlobalVariableGuid, name2, &data, &data_size, &attributes);
  OsIndications = data[0] & 0xff;
  printf("%s\n", name2);
  printf("%x\n", OsIndications);
  printf("%x\n", data_size);
  printf("%x\n", attributes);

  return 0;
}
