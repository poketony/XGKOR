import sys
from pathlib import Path
from PIL import Image

def raw_to_bmp(raw_path, palette_bmp_path, out_bmp_path, width=None, height=None):
    raw_path = Path(raw_path)
    palette_bmp_path = Path(palette_bmp_path)
    out_bmp_path = Path(out_bmp_path)

    # 8bpp raw 읽기
    raw_data = raw_path.read_bytes()
    raw_size = len(raw_data)

    # 팔레트/크기 정보용 BMP 읽기
    pal_img = Image.open(palette_bmp_path)
    if pal_img.mode != "P":
        # 팔레트가 없으면 강제로 팔레트 이미지로 변환
        pal_img = pal_img.convert("P")

    if width is None or height is None:
        # 기본값: 참고 BMP 크기 사용
        width, height = pal_img.size

    pixel_count = width * height
    header_size = raw_size - pixel_count
    if header_size <= 0:
        raise ValueError(f"헤더 크기 계산 오류: raw({raw_size}) - {width}*{height} = {header_size}")

    header = raw_data[:header_size]
    pixels = raw_data[header_size:]

    if len(pixels) < pixel_count:
        raise ValueError(f"픽셀 데이터가 부족합니다: {len(pixels)} < {pixel_count}")
    elif len(pixels) > pixel_count:
        # 편의상 초과분은 잘라 버린다
        pixels = pixels[:pixel_count]

    # 팔레트 이미지 생성
    img = Image.frombytes("P", (width, height), pixels)
    img.putpalette(pal_img.getpalette())

    img.save(out_bmp_path)
    print(f"[raw2bmp] {raw_path} -> {out_bmp_path}")
    print(f"  width={width}, height={height}, header_size={header_size}")


def bmp_to_raw(template_raw_path, bmp_path, out_raw_path, width=None, height=None):
    template_raw_path = Path(template_raw_path)
    bmp_path = Path(bmp_path)
    out_raw_path = Path(out_raw_path)

    # 원본 raw (헤더 복사용)
    template_raw = template_raw_path.read_bytes()
    template_size = len(template_raw)

    # 편집한 bmp
    img = Image.open(bmp_path)
    if img.mode != "P":
        # 인덱스 이미지가 아니면 팔레트 이미지로 변환
        img = img.convert("P")

    if width is None or height is None:
        width, height = img.size

    pixel_count = width * height
    header_size = template_size - pixel_count
    if header_size <= 0:
        raise ValueError(f"헤더 크기 계산 오류: template_raw({template_size}) - {width}*{height} = {header_size}")

    header = template_raw[:header_size]

    pixels = img.tobytes()
    if len(pixels) < pixel_count:
        raise ValueError(f"BMP 픽셀 데이터가 부족합니다: {len(pixels)} < {pixel_count}")
    elif len(pixels) > pixel_count:
        pixels = pixels[:pixel_count]

    new_raw = header + pixels

    if len(new_raw) != template_size:
        # 이론상 같아야 함
        raise ValueError(f"출력 RAW 크기가 원본과 다릅니다: {len(new_raw)} != {template_size}")

    out_raw_path.write_bytes(new_raw)
    print(f"[bmp2raw] {bmp_path} -> {out_raw_path}")
    print(f"  width={width}, height={height}, header_size={header_size}")


def main():
    if len(sys.argv) < 2:
        print("사용법:")
        print("  raw -> bmp : python xeno_raw_bmp.py raw2bmp <raw> <palette_bmp> <out_bmp> [width height]")
        print("  bmp -> raw : python xeno_raw_bmp.py bmp2raw <template_raw> <edited_bmp> <out_raw> [width height]")
        sys.exit(1)

    mode = sys.argv[1].lower()

    if mode == "raw2bmp":
        if len(sys.argv) < 5:
            print("사용법: python xeno_raw_bmp.py raw2bmp <raw> <palette_bmp> <out_bmp> [width height]")
            sys.exit(1)
        raw_path = sys.argv[2]
        palette_bmp = sys.argv[3]
        out_bmp = sys.argv[4]
        width = int(sys.argv[5]) if len(sys.argv) > 5 else None
        height = int(sys.argv[6]) if len(sys.argv) > 6 else None
        raw_to_bmp(raw_path, palette_bmp, out_bmp, width, height)

    elif mode == "bmp2raw":
        if len(sys.argv) < 5:
            print("사용법: python xeno_raw_bmp.py bmp2raw <template_raw> <edited_bmp> <out_raw> [width height]")
            sys.exit(1)
        template_raw = sys.argv[2]
        edited_bmp = sys.argv[3]
        out_raw = sys.argv[4]
        width = int(sys.argv[5]) if len(sys.argv) > 5 else None
        height = int(sys.argv[6]) if len(sys.argv) > 6 else None
        bmp_to_raw(template_raw, edited_bmp, out_raw, width, height)

    else:
        print(f"알 수 없는 모드: {mode}")
        sys.exit(1)


if __name__ == "__main__":
    main()
