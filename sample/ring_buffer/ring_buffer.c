#if 0
这是一个循环buffer的读写方式，构建方式值得学习：

1. circle buffer的初始化：

初始化buffer的地址，长度和读写指针。


2. circle buffer的读取函数：
HI_U32 circ_buf_read(circ_buf *pst_cb, HI_U8 *p_dest, HI_U32 len)
{
    HI_U8 *p_vir_addr = NULL;
    HI_U32 rd_len[2] = { 0, 0 }; // len 2
    HI_U32 rd_pos[2] = { 0, 0 }; // len 2
    HI_U32 i;
    HI_U32 read_pos, write_pos;
    HI_S32 ret;


    read_pos = *(pst_cb->pu32_read);
    write_pos = *(pst_cb->pu32_write);

    rd_pos[0] = read_pos;
    if (write_pos >= read_pos) {
        if (write_pos >= read_pos + len) {
            rd_len[0] = len;
        } else {
            rd_len[0] = write_pos - read_pos;
        }
  } else {
        if (read_pos + len <= pst_cb->lenght) {
            rd_len[0] = len;
        } else {
            rd_len[0] = pst_cb->lenght - read_pos;
            rd_pos[1] = 0;
            rd_len[1] = len - rd_len[0];
            if (write_pos < rd_len[1]) {
                rd_len[1] = write_pos;
            }
        }
    }

    for (i = 0; (i < 2) && (rd_len[i] != 0); i++) { // 2 is a number
        p_vir_addr = (HI_U8 *)(pst_cb->pu8_data + rd_pos[i]);

        ret = memcpy_s(p_dest, rd_len[i], p_vir_addr, rd_len[i]);
        is_memcpy_s_failed(ret);

        p_dest += rd_len[i];

        read_pos = rd_pos[i] + rd_len[i];
    }

    if (read_pos > pst_cb->lenght) {
        HI_LOG_ERR("read_pos is biger than pst_cb->lenght!\n");
        hi_err_print_u32(read_pos);
        hi_err_print_u32(pst_cb->lenght);
    }
    if (read_pos >= pst_cb->lenght) {
        read_pos = 0;
    }
  *(pst_cb->pu32_read) = read_pos;
    return rd_len[0] + rd_len[1];
}


3. circle buffer的写入函数：
HI_U32 circ_buf_write(circ_buf *pst_cb, HI_U8 *p_dest, HI_U32 len, HI_BOOL b_data_from_kernel)
{
    HI_U32 *p_vir_addr = HI_NULL;

    HI_U32 wt_len[2] = { 0, 0 }; // len 2
    HI_U32 wt_pos[2] = { 0, 0 }; // len 2
    HI_U32 i;
    HI_U32 read_pos, write_pos;
    HI_S32 ret;
    read_pos = *(pst_cb->pu32_read);
    write_pos = *(pst_cb->pu32_write);

    wt_pos[0] = write_pos;
    if (write_pos >= read_pos) {
        if (pst_cb->lenght >= (write_pos + len)) {
            wt_len[0] = len;
        } else {
            wt_len[0] = pst_cb->lenght - write_pos;
            wt_len[1] = len - wt_len[0];

            wt_pos[1] = 0;
        }
 } else {
        if (read_pos > (write_pos + len)) {
            wt_len[0] = len;
        } else {
            wt_len[0] = read_pos - write_pos;
        }
    }

    for (i = 0; (i < 2) && (wt_len[i] != 0); i++) { // 2 is a number
        p_vir_addr = (HI_U32 *)((HI_VOID *)pst_cb->pu8_data + wt_pos[i]);
        if (p_dest != HI_NULL) {
            if (b_data_from_kernel != HI_FALSE) {
                ret = memcpy_s(p_vir_addr, wt_len[i], p_dest, wt_len[i]);
                is_memcpy_s_failed(ret);

                p_dest = p_dest + wt_len[i];
                write_pos = wt_pos[i] + wt_len[i];
                continue;
            }


            ret = memcpy_s(p_vir_addr, p_dest, wt_len[i]);
            is_memcpy_s_failed(ret);


            p_dest = p_dest + wt_len[i];
        } else {  // only passthrouth send 0
            ret = memset_s(p_vir_addr, wt_len[i], 0, wt_len[i]);
            is_memset_s_failed(ret);
        }
 write_pos = wt_pos[i] + wt_len[i];
    }

    if (write_pos > pst_cb->lenght) {
        HI_LOG_ERR("write_pos is biger than pst_cb->lenght!\n");
        hi_err_print_u32(write_pos);
        hi_err_print_u32(pst_cb->lenght);
    }
    if (write_pos >= pst_cb->lenght) {
        write_pos = 0;
    }
    *(pst_cb->pu32_write) = write_pos;
    return wt_len[0] + wt_len[1];
}

这里的取巧之处就是构建了一个循环buffer，考虑到读写指针的先后顺序不一样，值得细细研读。
#endif