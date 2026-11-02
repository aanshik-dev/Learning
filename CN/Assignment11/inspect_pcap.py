import struct

def parse_pcap(filepath):
    with open(filepath, 'rb') as f:
        raw = f.read()

    offset = 24
    pkt_idx = 1
    while offset < len(raw):
        ts_sec, ts_usec, incl_len, orig_len = struct.unpack('<IIII', raw[offset:offset+16])
        offset += 16
        pkt_data = raw[offset:offset+incl_len]
        offset += incl_len

        eth_type = struct.unpack('!H', pkt_data[12:14])[0]
        if eth_type == 0x0800:
            ip_header = pkt_data[14:34]
            src_ip = '.'.join(str(b) for b in ip_header[12:16])
            dst_ip = '.'.join(str(b) for b in ip_header[16:20])
            proto = ip_header[9]
            ihl = (ip_header[0] & 0x0f) * 4
            if proto == 6:
                tcp_data = pkt_data[14+ihl:]
                src_port, dst_port, seq, ack, offset_flags = struct.unpack('!HHIIH', tcp_data[:14])
                tcp_hl = ((offset_flags >> 12) & 0x0f) * 4
                payload = tcp_data[tcp_hl:]
                print(f"Packet {pkt_idx}: TCP {src_ip}:{src_port} -> {dst_ip}:{dst_port}, payload: {len(payload)} bytes")
                p_off = 0
                while p_off < len(payload):
                    if payload[p_off:p_off+16] == b'\xff'*16:
                        bgp_len, bgp_type = struct.unpack('!HB', payload[p_off+16:p_off+19])
                        type_names = {1: 'OPEN', 2: 'UPDATE', 3: 'NOTIFICATION', 4: 'KEEPALIVE'}
                        tname = type_names.get(bgp_type, 'UNKNOWN')
                        print(f"  -> BGP Message: Type {bgp_type} ({tname}), Length: {bgp_len}")
                        if bgp_type == 2:
                            unf_len = struct.unpack('!H', payload[p_off+19:p_off+21])[0]
                            attr_len_offset = p_off + 21 + unf_len
                            attr_len = struct.unpack('!H', payload[attr_len_offset:attr_len_offset+2])[0]
                            attrs = payload[attr_len_offset+2:attr_len_offset+2+attr_len]
                            nlri = payload[attr_len_offset+2+attr_len:p_off+bgp_len]
                            prefix_len = nlri[0]
                            prefix_bytes = nlri[1:]
                            full_bytes = prefix_bytes + b'\x00'*(4 - len(prefix_bytes))
                            prefix_str = '.'.join(str(b) for b in full_bytes)
                            print(f"     NLRI (Advertised Prefix): {prefix_str}/{prefix_len}")
                            a_off = 0
                            while a_off < len(attrs):
                                flags = attrs[a_off]
                                code = attrs[a_off+1]
                                ext = bool(flags & 0x10)
                                if ext:
                                    length = struct.unpack('!H', attrs[a_off+2:a_off+4])[0]
                                    val = attrs[a_off+4:a_off+4+length]
                                    a_off += 4 + length
                                else:
                                    length = attrs[a_off+2]
                                    val = attrs[a_off+3:a_off+3+length]
                                    a_off += 3 + length
                                attr_names = {1: 'ORIGIN', 2: 'AS_PATH', 3: 'NEXT_HOP', 4: 'MULTI_EXIT_DISC', 5: 'LOCAL_PREF'}
                                aname = attr_names.get(code, 'OTHER')
                                print(f"     Path Attribute: Type {code} ({aname}), Length {length}")
                                if code == 2:
                                    seg_type = val[0]
                                    seg_len = val[1]
                                    as_nums = struct.unpack(f'!{seg_len}H', val[2:])
                                    print(f"       AS_PATH Segment Type: {seg_type} (2=AS_SEQUENCE), Path: {list(as_nums)}")
                        p_off += bgp_len
                    else:
                        break
        pkt_idx += 1

if __name__ == '__main__':
    parse_pcap('Assignment11/lab9_bgp_session.pcap')

