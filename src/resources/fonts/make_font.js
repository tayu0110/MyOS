const fs = require('fs')

const hankaku_txt = fs.readFileSync('./hankaku16.txt', { encoding: 'utf-8', flag: 'r' })
const hankaku_data = hankaku_txt.split('\n')

let write_flag = false
const buf = Buffer.alloc(4096)
let encoding_num = 0
let count_offset = 0
for(const str of hankaku_data) {
  if(str.substr(0, 8) === 'ENCODING') {
    encoding_num = parseInt(str.substr(9), 10)
  } else if(str.substr(0, 6) === 'BITMAP') {
    write_flag = true
  } else if(str.substr(0, 7) === 'ENDCHAR') {
    write_flag = false
    count_offset = 0
  } else {
    if(!write_flag) continue
    let bits = 0;
    for(const bit of str) {
      bits = bits * 2 + (bit === '@' ? 1 : 0)
    }
    buf.writeUIntLE(bits, 16 * encoding_num + count_offset, 1)
    count_offset++
  }
}
fs.writeFileSync('./hankaku16.bin', buf)