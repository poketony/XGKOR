<img width="1920" height="1080" alt="Image" src="https://github.com/user-attachments/assets/23c2988a-c426-4d16-bf17-cb118b3fdb4d" />

# Xenogears Korean Localization Workspace

이 저장소는 《제노기어스》 한국어판 제작에 실제로 사용한 번역 자료, 변환 도구, 빌드 작업 환경과 조사 기록을 보존한 작업 공간입니다. 필드 대사뿐 아니라 메뉴와 전투 문구, 아이템·기술명, 폰트와 UI 그래픽, 월드맵, 컷신까지 서로 다른 형식의 데이터를 다루며, 편집한 파일을 두 장의 디스크 이미지로 다시 구성하는 흐름을 담고 있습니다.

완성된 파일만 모아 둔 배포 저장소가 아니라, 일본어·영어 자료와 한국어 작업본을 비교하고 변환 과정을 다시 확인할 수 있도록 중간 산출물과 도구 소스, 작업 기록을 함께 남겨 두었습니다. 오래된 Windows 도구가 중심이라 사용 방식이 현대적이지는 않지만, 파일 번호와 포맷별 제약을 지키면 작업 과정을 재현할 수 있습니다.

원작과 제작진을 존중하는 독립 커뮤니티 프로젝트이며 공식 프로젝트와는 관련이 없습니다. 디스크 이미지는 포함하지 않으며, 빌드에는 사용자가 소유한 원본이 필요합니다.

> **English summary:** A working archive of the Xenogears Korean localization project: translated field and battle scripts, menu/kernel data, fonts, mapped UI graphics, world-map assets, cutscene notes, legacy Windows utilities, source code, and a reproducible two-disc rebuild workspace. Start in [`XenogearsWorkSpace`](./XenogearsWorkSpace/).

## Project status

The repository records the production workspace for the `1.0` build and later terminology corrections. It is best treated as a maintained research and rebuild archive, not as an installer or a ready-to-run game image.

- The staged rebuild directory currently contains 815 numbered replacement files.
- Disc 1 and Disc 2 rebuild lists and batch entry points are present.
- Editable Korean text, rebuilt binaries, reference data, tool binaries, and available tool source are kept together.
- There is no automated test suite or release packaging pipeline. Validation is file-level plus an end-to-end runtime test of a locally rebuilt image.

## What is in the repository

| Path | Purpose |
| --- | --- |
| [`CD1JAP`](./CD1JAP/) / [`CD2JAP`](./CD2JAP/) | Japanese reference scripts and extracted data organized by subsystem. |
| [`CD1KOR`](./CD1KOR/) / [`CD2KOR`](./CD2KOR/) | Korean field/battle scripts, menus, enemies, skill/item data, and world-map work files. |
| [`Toolkit`](./Toolkit/) | Windows utilities, table files, mapping workspaces, legacy source code, and the original English tool guide. |
| [`XenogearsWorkSpace`](./XenogearsWorkSpace/) | Canonical rebuild environment, replacement staging directory, command lists, and Disc 1/2 batch entry points. |
| [`기타 자료`](./기타%20자료/) | Translation sheets, font and graphics research, save data, cutscene workspace, file index, and production notes. |

The main editable field-script corpus is under [`CD1KOR/FieldScript/11`](./CD1KOR/FieldScript/11/). The binary files use the same four-digit file number as their UTF-8 text counterparts; for example, `0614.txt` documents the editable script and `0614.kor` is the rebuilt room file.

## End-to-end workflow

```text
user-owned raw disc image
        |
        v
extract numbered files -----> compare Japanese / English / Korean work trees
                                      |
                                      v
                         edit scripts, tables, fonts, UI maps
                                      |
                                      v
                       rebuild compressed files and archives
                                      |
                                      v
                 stage only numbered outputs in STRIPCD1(KOR)
                                      |
                                      v
                         rebuild Disc 1 or Disc 2 image
                                      |
                                      v
                    inspect log, then test the rebuilt image
```

Three container types appear repeatedly:

| Data type | Tool chain |
| --- | --- |
| A single compressed file | `xenocomp -d` -> edit -> `xenocomp -c` |
| An archive whose members are individually compressed | `xenopack -u` -> edit `file0`, `file1`, ... -> `xenopack -p` |
| A compressed multi-file archive | `xenocomp -d` -> `extXeno -e` -> edit `NN.xen` -> `extXeno -c` -> `xenocomp -c` |

## Requirements

- Windows with PowerShell and CMD support. The supplied executables and batch files are native Windows programs.
- At least 3 GB of free space, as recommended by the original tool guide; keep additional space for backups and both rebuilt images.
- User-owned North American raw BIN images with 2352-byte sectors. The current rebuild lists use these exact names:
  - `XenogearsUSACD1.bin`
  - `XenogearsUSACD2.bin`
- A separate graphics editor for indexed/RAW image work. Cutscene reconstruction additionally needs a video/frame converter, a Java runtime, and a sector-aware media replacement utility.

Keep the repository in a path without spaces. Several legacy parsers read paths as whitespace-delimited tokens and use fixed-size path buffers.

## Quick start: rebuild the staged Korean images

The checked-in replacement set is already flat and staged in [`XenogearsWorkSpace/STRIPCD1(KOR)`](./XenogearsWorkSpace/STRIPCD1%28KOR%29/). Do not copy the entire `CD1KOR` or `CD2KOR` tree into it.

1. Copy your original BIN files into `XenogearsWorkSpace` using the exact names above.
2. Open PowerShell at the repository root.
3. Record the input hashes so you can identify your own source images later:

   ```powershell
   Set-Location .\XenogearsWorkSpace
   Get-FileHash .\XenogearsUSACD1.bin -Algorithm SHA256
   Get-FileHash .\XenogearsUSACD2.bin -Algorithm SHA256
   ```

4. Run one build at a time from `XenogearsWorkSpace`:

   ```powershell
   .\cd1_rebuild.bat
   .\cd2_rebuild.bat
   ```

5. When debug mode asks whether to continue, enter `y`. The resulting files are:

   | Batch | Input | Output |
   | --- | --- | --- |
   | `cd1_rebuild.bat` | `XenogearsUSACD1.bin` | `XenogearsKORCD1.bin` |
   | `cd2_rebuild.bat` | `XenogearsUSACD2.bin` | `XenogearsKORCD2.bin` |

`xenoiso` opens the input read-only, rebuilds file positions, updates both archive indices, writes Mode 2 sector headers and EDC/ECC data for rebuilt data sectors, and copies the leading movie area unchanged. The output path is opened with overwrite semantics before the confirmation prompt, so preserve any previous output under another name. Input and output names must never be the same.

The batch file temporarily moves `0022.rootexecd1` or `0022.rootexecd2` into the flat staging directory. If the process is interrupted, move that one file back to the `XenogearsWorkSpace` root before retrying.

## Staging and naming rules

`xenoiso` directory mode is non-recursive. It derives the destination file number with the leading decimal digits of each filename; the extension is descriptive only.

| Work result | Final staged form | Rule |
| --- | --- | --- |
| Field room `0614.kor` | `STRIPCD1(KOR)\0614.kor` | Keep the `0614` prefix unchanged. |
| Rebuilt kernel `0029.korcmp` | `STRIPCD1(KOR)\0029.korcmp` | Stage the final recompressed archive, not its `.xen` members. |
| Rebuilt menu `2593.kor` | `STRIPCD1(KOR)\2593.kor` | Stage the packed outer archive, not `file0`, `file1`, etc. |
| World map `3964.Korcmp` | `STRIPCD1(KOR)\3964.Korcmp` | Stage the final compressed archive only. |
| Disc executable | `0022.rootexecd1` or `0022.rootexecd2` at workspace root | The matching batch stages and restores it automatically. |

Before a build, the staging directory must contain only flat files with unique numeric prefixes. Subdirectories are ignored, non-numeric names resolve incorrectly, and duplicate numeric prefixes make the selected replacement ambiguous. Disc 2 uses `cd2fix`, which subtracts five from each Disc 1-style file number to account for the different movie count.

The repository does not use `.new`, `_patched`, or `_rebuilt` as a finalization convention. Existing suffixes such as `.kor`, `.korcmp`, `.kordec`, `.menuexe`, and `.battlescript` describe working state or content; the leading number is what controls placement.

## Tool reference

### Xenolater++ - field and battle text

- **Entry point:** [`Toolkit/Xenolater++/xenolater.exe`](./Toolkit/Xenolater%2B%2B/xenolater.exe)
- **Run from:** `Toolkit\Xenolater++`, so its table files are easy to select.
- **Field input:** numbered room files such as `CD1KOR\FieldScript\11\0614.kor`, opened with **Open**.
- **Archive-member input:** battle or system dialogue members, opened with **Open dump**.
- **Tables:** decode with `xeno_jap_fix.tbl`; encode Korean text with `xeno_kor_fix.tbl`.
- **Output:** saving rewrites/rebuilds the loaded binary; Export creates an editable text dump. The tracked Korean `.txt` corpus is UTF-8, although a fresh export from the legacy UI may need conversion from Shift-JIS.

Preserve tags such as `<TextBlock ...>`, `<Delay ...>`, `<New>`, `<Close>`, and `<End of Block>`. Enable Auto Count when resizing ordinary dialogue windows. Project notes cap the normal dialogue width at `w:55`; portrait windows, scrolling dialogue, and fixed-position choices need manual review. Do not add lines above a choice arrow without checking its fixed screen position.

See [`Toolkit/Xenolater++/사용법.txt`](./Toolkit/Xenolater%2B%2B/%EC%82%AC%EC%9A%A9%EB%B2%95.txt) for the short Korean workflow.

### Xenocomp - compression and decompression

- **Entry point:** `Toolkit\xenogears_translation_tools\xenocomp.exe`
- **Syntax:**

  ```powershell
  .\xenocomp.exe -d 0029.korcmp 0029.kordec
  .\xenocomp.exe -c 0029.kordec 0029.korcmp
  ```

The first filename is always the input and the second is the output. The output is opened with overwrite semantics. The tool does not create a backup or verify a source hash.

### ExtXeno - compressed-archive members

- **Entry point:** `Toolkit\xenogears_translation_tools\extXeno.exe`
- **Syntax:**

  ```powershell
  .\extXeno.exe -e 0047.kordec 0047_members
  .\extXeno.exe -c 0047.kordec 01.xen 02.xen
  ```

Extraction creates sequential names such as `01.xen`, `02.xen`, and so on. Creation uses member order exactly as supplied and overwrites the destination archive. The maintained `0029`, `0047`, and world-map work directories include `repack.bat` files that pass their complete `*.xen` set in the established order.

Every `.xen` member in this archive family must have a byte length divisible by four. ExtXeno does not enforce this; pad a short member with `00` bytes before repacking. All 315 `.xen` files currently stored under `CD1KOR` satisfy this rule.

### Xenopack - archives of compressed members

- **Entry point:** `Toolkit\xenogears_translation_tools\xenopack.exe`
- **Syntax:**

  ```powershell
  .\xenopack.exe -u 2593.unk8
  .\xenopack.exe -p 2593.unk8
  ```

Run it in a dedicated working directory. Unpack writes `file0`, `file1`, and later members into the current directory; pack rebuilds and overwrites the named archive from those files. Typical users include `2593`/`3958` menu data, `2614` battle UI data, and `3088` battle dialogue. Reinsert only the rebuilt outer archive into the final staging directory.

### ImgConv and Xenomap - mapped UI graphics

- **Work areas:** [`Toolkit/xenogears_translation_tools/xenomaps`](./Toolkit/xenogears_translation_tools/xenomaps/)
- **4 bpp to 8 bpp:** `imgconv.exe -48 source.raw editable.raw`
- **8 bpp to 4 bpp:** `imgconv.exe -84 editable.raw rebuilt.raw`

Xenomap edits the piece mapping used to compose battle and menu labels: source coordinates, on-screen coordinates, dimensions, flips, and per-piece metadata. The RAW file is for preview; the mapping file is the file that Xenomap saves.

Keep the rebuilt 4 bpp region exactly the same byte length as the original region. Graphics editors may append padding. Xenomap also exposes an `Other` field containing palette-related and still-unknown metadata; when adding a piece, copy this field from a compatible existing piece instead of leaving it blank. Keep palette blocks and unrelated archive members unchanged, then rebuild the outer archive with Xenopack.

### Xenoiso - complete disc rebuild

- **Entry point:** `XenogearsWorkSpace\xenoiso.exe`
- **Syntax:** `xenoiso list.txt [-d]`
- **Current lists:** [`cd1list.txt`](./XenogearsWorkSpace/cd1list.txt) and [`cd2list.txt`](./XenogearsWorkSpace/cd2list.txt)
- **Debug mode:** `-d` overwrites `log.txt` and asks for confirmation before the long copy phase.

A list file contains disc mode, input image, output image, and one or more `number,path` entries. `-1,directory` activates flat directory mode. Xenoiso relocates later files when replacements grow, so it is the rebuild path for outputs that no longer fit their original allocation.

It does not validate an expected image size or hash. It also does not replace the movie area; that area is copied from the input image. Use the supplied batch files for the repository's staged build instead of invoking the lists from another working directory.

### Legacy single-file and cutscene workflows

The toolkit also contains GUI utilities for replacing one numbered file in place. They are useful for small experiments, but their safety checks are limited to the original sector allocation; use Xenoiso for production rebuilds or any enlarged file.

The cutscene process is preserved under [`기타 자료/STR WorkSpace`](./기타%20자료/STR%20WorkSpace/). Its numbered batch files cover frame extraction, replacement-list generation, audio/frame application, and sample-exact audio correction. Treat this as a recorded workstation recipe, not a portable quick start: `3. ApplyingMaterial.bat` contains machine-specific absolute paths that must be changed, and `0. png_eliminator.bat` deletes every PNG in `Frames` after confirmation.

## Validation

There is no unit-test command. Use these narrow checks before the final runtime test.

Check the four-byte archive-member rule:

```powershell
$bad = Get-ChildItem .\CD1KOR -Recurse -File -Filter *.xen |
  Where-Object { $_.Length % 4 -ne 0 }
if ($bad) { $bad | Select-Object FullName, Length; throw 'Unaligned .xen member' }
```

Check the flat staging names and duplicate numeric prefixes:

```powershell
$files = Get-ChildItem '.\XenogearsWorkSpace\STRIPCD1(KOR)' -File
$badNames = $files | Where-Object Name -NotMatch '^\d+'
$duplicates = $files | ForEach-Object {
  if ($_.Name -match '^(\d+)') { [int]$Matches[1] }
} | Group-Object | Where-Object Count -GT 1
if ($badNames -or $duplicates) { throw 'Invalid rebuild staging set' }
```

After rebuilding:

1. Confirm that `log.txt` ends with a successful completion message and contains no file-open error.
2. Confirm the output BIN is non-empty and distinct from the input hash.
3. Test boot, save/load, field transitions, menus, battles, world-map labels, and any changed cutscenes in an accurate runtime environment. Older, permissive environments may not expose alignment errors.

## Known limitations

- The supplied applications are legacy Windows binaries with terse or non-English interfaces.
- Paths containing spaces are unsafe in Xenoiso list files.
- Directory insertion is flat and non-recursive; filenames must begin with the intended file number.
- Output files are commonly overwritten without backup. Work on copies and keep the original disc images read-only.
- Xenoiso has no source-image hash check and cannot replace the movie area.
- ExtXeno does not enforce the required four-byte member alignment.
- Xenomap can overwrite a mapping file in place and may fail on incompatible preview data; save a backup before editing.
- Several text areas have fixed byte or layout limits, including 16 bytes for world-map location labels, 13 characters for monster names, 28 for monster techniques, and exactly 15 characters per chapter-title line in the legacy format.

For deeper format notes, consult the original [`translation tools user's guide`](./Toolkit/xenogears_translation_tools/xenogears_translation_tools_user%27s_guide.pdf), [`기타 자료/파일 번호별 데이터.txt`](./기타%20자료/%ED%8C%8C%EC%9D%BC%20%EB%B2%88%ED%98%B8%EB%B3%84%20%EB%8D%B0%EC%9D%B4%ED%84%B0.txt), and [`기타 자료/제노기어스 작업 기록.txt`](./기타%20자료/%EC%A0%9C%EB%85%B8%EA%B8%B0%EC%96%B4%EC%8A%A4%20%EC%9E%91%EC%97%85%20%EA%B8%B0%EB%A1%9D.txt).

## Acknowledgements

This workspace exists because of the original Xenogears team and the many community translators and researchers who kept studying the game over the years. The bundled translation-tool suite and its source preserve the work of the SadNES cITy contributors; the Korean Xenolater notes also credit 그미래 for porting the updated editor. The Korean scripts, terminology records, graphics experiments, and build history reflect sustained work by the Korean localization community.
