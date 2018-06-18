INCLUDE_PATH=-Ibase64 -IcJSON -Iqiniu

SOURCE_FILES=\
    b64/b64.c\
    b64/urlsafe_b64.c\
    cJSON/cJSON.c\
    qiniu/auth_mac.c\
    qiniu/base.c\
    qiniu/base_io.c\
    qiniu/cdn.c\
    qiniu/conf.c\
    qiniu/fop.c\
    qiniu/http.c\
    qiniu/io.c\
    qiniu/macro.h\
    qiniu/qetag.c\
    qiniu/reader.c\
    qiniu/resumable_io.c\
    qiniu/rs.c\
    qiniu/tm.c\

all: $(SOURCE_FILES)
	gcc -g -c -fPIC $^ $(INCLUDE_PATH) -lcurl -lcrypto -lssl -lm
