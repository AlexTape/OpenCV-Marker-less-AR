#ifndef __GLMETASEQ_H__
#define __GLMETASEQ_H__

/*=========================================================================================
 ���^�Z�R�C�A�ō쐬�������f��(*.mqo)��OpenGL��ɓǂݍ��ފ֐����܂Ƃ߂�C/C++�p�w�b�_
 =========================================================================================*/

/*
 GLMetaseq
 The MIT License
 Copyright (c) 2009 Sunao Hashimoto and Keisuke Konishi

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.


 GLMetaseq
 MIT���C�Z���X
 Copyright (c) 2009 Sunao Hashimoto and Keisuke Konishi

 �ȉ��ɒ�߂�����ɏ]���A�{�\�t�g�E�F�A����ъ֘A�����̃t�@�C���i�ȉ��u�\�t�g
 �E�F�A�v�j�̕������擾���邷�ׂĂ̐l�ɑ΂��A�\�t�g�E�F�A�𖳐����Ɉ������Ƃ�
 �����ŋ����܂��B����ɂ́A�\�t�g�E�F�A�̕������g�p�A���ʁA�ύX�A�����A�f�ځA
 �Еz�A�T�u���C�Z���X�A�����/�܂��͔̔����錠���A����у\�t�g�E�F�A��񋟂���
 ����ɓ������Ƃ������錠�����������Ɋ܂܂�܂��B

 ��L�̒��쌠�\������і{����\�����A�\�t�g�E�F�A�̂��ׂĂ̕����܂��͏d�v�ȕ���
 �ɋL�ڂ�����̂Ƃ��܂��B

 �\�t�g�E�F�A�́u����̂܂܁v�ŁA�����ł��邩�Öقł��邩���킸�A����̕ۏ�
 ���Ȃ��񋟂���܂��B�����ł����ۏ؂Ƃ́A���i���A����̖ړI�ւ̓K�����A�����
 ������N�Q�ɂ��Ă̕ۏ؂��܂݂܂����A����Ɍ��肳�����̂ł͂���܂���B
 ��҂܂��͒��쌠�҂́A�_��s�ׁA�s�@�s�ׁA�܂��͂���ȊO�ł��낤�ƁA�\�t�g
 �E�F�A�ɋN���܂��͊֘A���A���邢�̓\�t�g�E�F�A�̎g�p�܂��͂��̑��̈�����
 ����Đ������؂̐����A���Q�A���̑��̋`���ɂ��ĉ���̐ӔC������Ȃ�����
 �Ƃ��܂��B
 */

/*
 ----------------------------------------------------------------------------------------
 1. ���̃w�b�_���g����ł̒��ӓ_
 ----------------------------------------------------------------------------------------

 ���ǂݍ��݉\�ȃe�N�X�`���̉摜�`����bmp�Ctga�Cjpeg�Cpng
 �@������
 �@�@jpeg�̓ǂݍ��݂ɂ�JPEG���C�u�����ilibjpeg.lib, jpeglib.h�j���ʓr�K�v
 �@�@jpeg�̓ǂݍ��݂�L��ɂ���ɂ́C���̃w�b�_�� DEF_USE_LIBJPEG �� 1 �ɂ��邱��

 �@	png�̓ǂݍ��݂ɂ�PNG���C�u�����ilibpng.lib, zlib.lib, png.h ,zlib.h�j���ʓr�K�v
 �@�@png�̓ǂݍ��݂�L��ɂ���ɂ́C���̃w�b�_�� DEF_USE_LIBPNG  �� 1 �ɂ��邱��

 ���e�N�X�`���摜�̃T�C�Y�́u��ӂ�2��n��T�C�Y(64,128,256�c)�̐���`�v�Ɍ���


 ----------------------------------------------------------------------------------------
 2. �g����(1) 1��MQO�t�@�C����ǂݍ���ŕ\������ꍇ
 ----------------------------------------------------------------------------------------

 (1) ����iARToolKit�̏ꍇ�CargInit()�̌�Ɏg�p�j

 mqoInit();

 (2) �t�@�C������̃��f���̓ǂݍ���

 MQO_MODEL model;
 model = mqoCreateModel( "mario.mqo", 1.0 );

 (3) ���f���̌Ăяo��

 mqoCallModel( model );

 (4) ���f���̏���

 mqoDeleteModel( model );

 (5) �I�������i�v���O�����I�����ɂ���Ă��������j

 mqoCleanup();

 ----------------------------------------------------------------------------------------
 3. �g����(2) �A�ԃt�@�C����ǂݍ���ŕ\������ꍇ
 ----------------------------------------------------------------------------------------

 (1) ����iARToolKit�̏ꍇ�CargInit()�̌�Ɏg�p�j

 mqoInit();

 (2) �A�ԃV�[�P���X�̍쐬

 �@��Fmario0.mqo �` mario9.mqo ��ǂݍ���

 MQO_SEQUENCE seq;
 seq = mqoCreateSequence( "mario%d.mqo", 10, 1.0 );

 (3) �A�ԃV�[�P���X�̎w��t���[���̌Ăяo���ii�̓t���[���ԍ��j

 mqoCallSequence( seq, i );

 (4) �A�ԃV�[�P���X�̏���

 mqoDeleteSequence( seq );

 (5) �I�������i�v���O�����I�����ɂ���Ă��������j

 mqoCleanup();

 ----------------------------------------------------------------------------------------
 4. ��Ȏd�l
 ----------------------------------------------------------------------------------------

 ���\���@�\
	�E�T�|�[�g���Ă���MQO�t�@�C���̃o�[�W�����́uMetasequoia Ver1.0/2.0�`2.4�v

 �E�Ή����Ă���ގ����
 �@�F�i���j
 �@�e�N�X�`���}�b�v�i�o���v�}�b�v��Ή��^UV�}�b�s���O�̂݁j

 �E�Ή����Ă���I�u�W�F�N�g���
 �@�\���^��\���̐؂�ւ�
 �@�X���[�W���O�̗L��
 �@���_�@������߂�Ƃ��̃X���[�W���O�p
 �@���_���
 �@�ʏ��i���_�J���[��Ή��j

 �E�ȖʁE���ʁE��]�̂ɂ͔�Ή�
 �E���^�{�[���͔�Ή�

 ���d�l
 �E�`�����N���͌����Ƃ��đ啶���Ə������̋�ʂ����Ȃ����ƂɂȂ��Ă��邪
 �@��ʂ��Ă��܂��Ă���D
 �E�e�N�X�`���̃p�X�ɑ��o�C�g�����������Ă���
 �@���̂Ȃ���'\'(0x5c)��'/'(0x2f)���͂����Ă���Ƃ��܂��e�N�X�`�����ǂ߂Ȃ��D
 �E�����F�̃}�e���A���ɑΉ����Ă��Ȃ��D
 �@Object�`�����N��face�`�����N�̍ގ��C���f�b�N�X�iM(%d)�j��-1�ɖ��Ή��D

 */

/*=========================================================================
 �y���[�U���C�ӂŐݒ�z
 =========================================================================*/

#define MAX_TEXTURE				100			// �e�N�X�`���̍ő��舵����
#define MAX_OBJECT				50			// 1��MQO�t�@�C�����̍ő�I�u�W�F�N�g��
#define SIZE_STR				256			// ������o�b�t�@�̃T�C�Y
#define DEF_IS_LITTLE_ENDIAN	1			// �G���f�B�A���w��iintel�n=1�j
#define DEF_USE_LIBJPEG			0			// libjpeg�̎g�p�i1:�g�p 0:���g�p�j
#define DEF_USE_LIBPNG			1			// libpng �̎g�p�i1:�g�p 0:���g�p�j

/*=========================================================================
 �y�R���p�C���I�v�V�����z
 =========================================================================*/

// JPEG���g�p����
#ifdef D_JPEG
#undef	DEF_USE_LIBJPEG
#define	DEF_USE_LIBJPEG 1
#endif

// JPEG���g�p���Ȃ�
#ifdef D_NO_JPEG
#undef	DEF_USE_LIBJPEG
#define	DEF_USE_LIBJPEG 0
#endif

// PNG���g�p����
#ifdef D_PNG
#undef	DEF_USE_LIBPNG
#define	DEF_USE_LIBPNG 1
#endif

// PNG���g�p���Ȃ�
#ifdef D_NO_PNG
#undef	DEF_USE_LIBPNG
#define	DEF_USE_LIBPNG 0
#endif

/*=========================================================================
 �y�w�b�_�z
 =========================================================================*/

#ifdef WIN32
#include <windows.h>
#else
#ifndef MAX_PATH
#define MAX_PATH    256
#endif
#ifndef TRUE
#define TRUE    (1==1)
#endif
#ifndef FALSE
#define FALSE   (1!=1)
#endif
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
//	#include <gl/glext.h>
#endif

/*=========================================================================
 �y�@�\�ݒ�z libjpeg�g�p�ݒ�
 =========================================================================*/

#if DEF_USE_LIBJPEG

#define XMD_H // INT16��INT32�̍Ē�`�G���[��h��
#ifdef FAR
#undef FAR
#endif

#include "jpeglib.h"
#pragma comment(lib,"libjpeg.lib")

#endif

/*=========================================================================
 �y�@�\�ݒ�z libpng�g�p�ݒ�
 =========================================================================*/

#if DEF_USE_LIBPNG

#include "png.h"
#include "zlib.h"
//#pragma comment(lib,"libpng.lib")
//#pragma comment(lib,"zlib.lib")

#endif

/*=========================================================================
 �y�}�N����`�z �ő�l�}�N��
 =========================================================================*/

#ifndef MAX
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#endif

/*=========================================================================
 �y�^��`�z TGA�t�H�[�}�b�g
 =========================================================================*/

#define DEF_TGA_COLOR_MAP_FLAG_VALID	1
#define DEF_TGA_TYPE_NON				0
#define DEF_TGA_TYPE_INDEX				1
#define DEF_TGA_TYPE_FULL				2
#define DEF_TGA_TYPE_MONO				3
#define DEF_TGA_TYPE_RLEINDEX			9
#define DEF_TGA_TYPE_RLEFULL			10
#define DEF_TGA_TYPE_RLEMONO			11
#define DEF_TGA_BIT_INFO_RIGHT_TO_LEFT	0x00
#define DEF_TGA_BIT_INFO_LEFT_TO_RIGHT	0x10
#define DEF_TGA_BIT_INFO_DOWN_TO_TOP	0x00
#define DEF_TGA_BIT_INFO_TOP_TO_DOWN	0x20

typedef struct {
	unsigned char id;
	unsigned char color_map_flag;
	unsigned char type;
	unsigned short color_map_entry;
	unsigned char color_map_entry_size;
	unsigned short x;
	unsigned short y;
	unsigned short width;
	unsigned short height;
	unsigned char depth;
	unsigned char bit_info;
} STR_TGA_HEAD;

/*=========================================================================
 �y�^��`�z OpenGL�p�F�\���� (4�Ffloat)
 =========================================================================*/
typedef struct {
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
} glCOLOR4f;

/*=========================================================================
 �y�^��`�z OpenGL�p�Q�������W�\���� (float)
 =========================================================================*/
typedef struct {
	GLfloat x;
	GLfloat y;
} glPOINT2f;

/*=========================================================================
 �y�^��`�z OpenGL�p�R�������W�\���� (float)
 =========================================================================*/
typedef struct tag_glPOINT3f {
	GLfloat x;
	GLfloat y;
	GLfloat z;
} glPOINT3f;

/*=========================================================================
 �y�^��`�z �ʏ��\����
 =========================================================================*/
typedef struct {
	int n;		// 1�̖ʂ��\�����钸�_�̐��i3�`4�j
	int m;		// �ʂ̍ގ��ԍ�
	int v[4];	// ���_�ԍ����i�[�����z��
	glPOINT2f uv[4];	// UV�}�b�v
} MQO_FACE;

/*=========================================================================
 �y�^��`�z �ގ����\���́i�t�@�C���������ǂݍ��ލۂɎg�p�j
 =========================================================================*/
typedef struct {
	glCOLOR4f col;				// �F
	GLfloat dif[4];				// �g�U��
	GLfloat amb[4];				// ��͌�
	GLfloat emi[4];				// ���ȏƖ�
	GLfloat spc[4];				// ���ˌ�
	GLfloat power;				// ���ˌ��̋���
	int useTex;				// �e�N�X�`���̗L��
	char texFile[SIZE_STR];	// �e�N�X�`���t�@�C��
	char alpFile[SIZE_STR];	// �A���t�@�e�N�X�`���t�@�C��
	GLuint texName;			// �e�N�X�`����
} MQO_MATDATA;

/*=========================================================================
 �y�^��`�z �I�u�W�F�N�g�\���́i�p�[�c�P�̃f�[�^�j
 =========================================================================*/
typedef struct {
	char objname[SIZE_STR];	// �p�[�c��
	int visible;			// �����
	int shading;			// �V�F�[�f�B���O�i0:�t���b�g�^1:�O���[�j
	float facet;				// �X���[�W���O�p
	int n_face;				// �ʐ�
	int n_vertex;			// ���_��
	MQO_FACE *F;					// ��
	glPOINT3f *V;					// ���_
} MQO_OBJDATA;

/*=========================================================================
 �y�^��`�z �e�N�X�`���v�[��
 =========================================================================*/
typedef struct {
	GLuint texture_id;			// �e�N�X�`��ID
	int texsize;			// �e�N�X�`���T�C�Y
	char texfile[MAX_PATH];	// �e�N�X�`���t�@�C��
	char alpfile[MAX_PATH];	// �A���t�@�e�N�X�`���t�@�C��
	unsigned char alpha;				// �A���t�@
} TEXTURE_POOL;

/*=========================================================================
 �y�^��`�z ���_�f�[�^�i�e�N�X�`���g�p���j
 =========================================================================*/
typedef struct {
	GLfloat point[3];	// ���_�z�� (x, y, z)
	GLfloat normal[3];	// �@��z�� (x, y, z)
	GLfloat uv[2];		// UV�z�� (u, v)
} VERTEX_TEXUSE;

/*=========================================================================
 �y�^��`�z ���_�f�[�^�i�e�N�X�`���s�g�p���j
 =========================================================================*/
typedef struct {
	GLfloat point[3];	// ���_�z�� (x, y, z)
	GLfloat normal[3];	// �@��z�� (x, y, z)
} VERTEX_NOTEX;

/*=========================================================================
 �y�^��`�z �}�e���A�����i�}�e���A���ʂɒ��_�z������j
 =========================================================================*/
typedef struct {
	int isValidMaterialInfo;	// �}�e���A�����̗L��/����
	int isUseTexture;		// �e�N�X�`���̗L���FUSE_TEXTURE / NOUSE_TEXTURE
	GLuint texture_id;			// �e�N�X�`���̖��O(OpenGL)
	GLuint VBO_id;				// ���_�o�b�t�@��ID(OpenGL)�@�Ή����Ă鎞�����g�p
	int datanum;			// ���_��
	GLfloat color[4];			// �F�z�� (r, g, b, a)
	GLfloat dif[4];				// �g�U��
	GLfloat amb[4];				// ��͌�
	GLfloat emi[4];				// ���ȏƖ�
	GLfloat spc[4];				// ���ˌ�
	GLfloat power;				// ���ˌ��̋���
	VERTEX_NOTEX *vertex_p;			// �|���S���݂̂̎��̒��_�z��
	VERTEX_TEXUSE *vertex_t;			// �e�N�X�`���g�p���̒��_�z��
} MQO_MATERIAL;

/*=========================================================================
 �y�^��`�z �����I�u�W�F�N�g�i1�̃p�[�c���Ǘ��j
 =========================================================================*/
typedef struct {
	char objname[SIZE_STR];		// �I�u�W�F�N�g��
	int isVisible;				// 0�F��\���@���̑��F�\��
	int isShadingFlat;			// �V�F�[�f�B���O���[�h
	int matnum;					// �g�p�}�e���A����
	MQO_MATERIAL *mat;					// �}�e���A���z��
} MQO_INNER_OBJECT;

/*=========================================================================
 �y�^��`�z MQO�I�u�W�F�N�g�i1�̃��f�����Ǘ��j�@��MQO_MODEL�̎���
 =========================================================================*/
typedef struct {
	unsigned char alpha;				// ���_�z��쐬���Ɏw�肳�ꂽ�A���t�@�l�i�Q�Ɨp�j
	int objnum;				// �����I�u�W�F�N�g��
	MQO_INNER_OBJECT obj[MAX_OBJECT];	// �����I�u�W�F�N�g�z��
} MQO_OBJECT;

/*=========================================================================
 �y�^��`�z MQO_MODEL�\����
 =========================================================================*/
typedef MQO_OBJECT * MQO_MODEL;		// MQO_MODEL�͓Ǝ��`���\���̂ւ̃A�h���X

/*=========================================================================
 �y�^��`�z MQO�V�[�P���X
 =========================================================================*/
typedef struct {
	MQO_MODEL model;		// ���f��
	int n_frame;	// �t���[����
} MQO_SEQUENCE;

/*=========================================================================
 �y�^��`�z glext.h ����� VBO Extension �̒�`
 =========================================================================*/
#ifdef WIN32
#define GL_ARRAY_BUFFER_ARB	0x8892
#define GL_STATIC_DRAW_ARB	0x88E4
typedef void (APIENTRY * PFNGLBINDBUFFERARBPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRY * PFNGLDELETEBUFFERSARBPROC) (GLsizei n, const GLuint *buffers);
typedef void (APIENTRY * PFNGLGENBUFFERSARBPROC) (GLsizei n, GLuint *buffers);
typedef void (APIENTRY * PFNGLBUFFERDATAARBPROC) (GLenum target, int size, const GLvoid *data, GLenum usage);
#endif

/*=========================================================================
 �y�O���[�o���ϐ���`�z
 =========================================================================*/

#ifdef __GLMETASEQ_C__
#define __GLMETASEQ_C__EXTERN
#else
#define __GLMETASEQ_C__EXTERN extern
#endif

__GLMETASEQ_C__EXTERN int g_isVBOSupported;	// OpenGL�̒��_�o�b�t�@�̃T�|�[�g�L��

#ifdef WIN32	
// VBO Extension �֐��̃|�C���^
__GLMETASEQ_C__EXTERN PFNGLGENBUFFERSARBPROC glGenBuffersARB;// VBO ���O����
__GLMETASEQ_C__EXTERN PFNGLBINDBUFFERARBPROC glBindBufferARB;// VBO ���т�
__GLMETASEQ_C__EXTERN PFNGLBUFFERDATAARBPROC glBufferDataARB;// VBO �f�[�^���[�h
__GLMETASEQ_C__EXTERN PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;// VBO �폜
#endif

#undef __GLMETASEQ_C__EXTERN

/*=========================================================================
 �y�֐��錾�z
 =========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

// ����
void mqoInit(void);

// �I������
void mqoCleanup(void);

// ���f������
MQO_MODEL mqoCreateModel(char *filename, double scale);

// �V�[�P���X����
MQO_SEQUENCE mqoCreateSequence(const char *format, int n_file, double scale);

// �V�[�P���X�����i�g���Łj
MQO_SEQUENCE mqoCreateSequenceEx(const char *format, int n_file, double scale,
		int fade_inout, unsigned char alpha);

// ���f���Ăяo��
void mqoCallModel(MQO_MODEL model);

// �V�[�P���X�Ăяo��
void mqoCallSequence(MQO_SEQUENCE seq, int i);

// ���f���̍폜
void mqoDeleteModel(MQO_MODEL model);

// �V�[�P���X�̍폜
void mqoDeleteSequence(MQO_SEQUENCE seq);

#ifdef __cplusplus
}
#endif

#endif	// -- end of header --

