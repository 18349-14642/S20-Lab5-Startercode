/* kernel.lds
 * Basic Linker Script
 *
 * 0x00000000 - 0x07ffffff - aliased to flash or sys memory depending on BOOT jumpers
 * 0x08000000 - 0x08080000 - Flash (64K ... or 128K)
 * 0x1ffff000 - 0x1ffff7ff - Boot firmware in system memory
 * 0x1ffff800 - 0x1fffffff - option bytes
 * 0x20000000 - 0x20018000 - SRAM (96k)
 * 0x40000000 - 0x40023400 - peripherals 
 */

SECTIONS
{
  /* Text and interrupt vector table.*/
  /*Toggle permissions between kernel_text_start and kernel_text_end*/
  .kernel_text 0x08000000 :
  {
    _kernel_text_start = .;
    _ivt_start = .;
    KEEP(*(.ivt))
    <K_OBJ_DIR>/*.o (.text*) /*END REGION*/
    . = ALIGN(2048); /* Align to the closest 2-byte boundary*/
    _kernel_text_end = .;
  }

  .app_text _user_text_start :
  {
    _user_text_start = .;
    KEEP(*(.swi_stub))
    <U_OBJ_DIR>/*.o (.text*) /*END REGION*/
    . = ALIGN(2048); /* Align to the closest 2-byte boundary*/
    _user_text_end = .;
  }

  . = ALIGN(2048);

  .rodata : 
  { 
    _k_rodata = .; 
    <K_OBJ_DIR>/*.o (.rodata*); /*END REGION*/
    . = ALIGN(512);
    _u_rodata = .;
    <U_OBJ_DIR>/*.o (.rodata*); /*END REGION*/
    *(.rodata);
    . = ALIGN(512);
    _u_erodata = .;
  }
  
  . = ALIGN(8);
  _erodata = . ;

  .data 0x20000000 : AT ( _erodata )
  {
    _k_data = .;
    <K_OBJ_DIR>/*.o (.data*); /*END REGION*/
    . = ALIGN(512);
    _u_data = .; 
    <U_OBJ_DIR>/*.o (.data*); /*END REGION*/
    *(.data);
    . = ALIGN(512);
    _u_edata = .;
  }

  .bss ALIGN(512) : 
  {
    _bss_start = .;
    _k_bss = .;
    <K_OBJ_DIR>/*.o (.bss*); /*END REGION*/
    <K_OBJ_DIR>/*.o (COMMON*); /*END REGION*/
    . = ALIGN(512);
    _u_ebss = .;
    <U_OBJ_DIR>/*.o (.bss*); /*END REGION*/
    <U_OBJ_DIR>/*.o (COMMON*); /*END REGION*/
    *(.bss) *(COMMON) ;
    _u_ebss = .;
  }

  /* Variables ld will declare for the start routine */
  _bss_size = ((_u_ebss) - (_k_bss));
  _data_size = ((_u_edata) - (_k_data));

  . = ALIGN(1024);
  . = . + 0x800;  /* 2kB of msp stack */
  __msp_stack_top = .;
  __kheap_low = .; /* for k_malloc */
  . = . + 0x10000; /* 70KB of k_heap */
  __kheap_top = .; /* for k_malloc */
  
  . = ALIGN(16*1024);
  __heap_low = .; /* for _sbrk */
  . = . + 0x3800; /* 14KB of heap */
  __heap_top = .; /* for _sbrk */
  . = . + 0x800;  /* 2kB processor memory */
  __psp_stack_top = .;

  end = .;
}
