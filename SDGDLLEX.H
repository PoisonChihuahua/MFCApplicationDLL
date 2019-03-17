//������������������������������������������������������������������������������������������������
//��SDGDLLEX.H                                                                                  ��
//������������������������������������������������������������������������������������������������
//���g��DLL�����A�w�b�_�t�@�C��                                                                 ��
//��ver.	1.00	2004/12/11                                                                  ��
//��ver.	1.01	2004/12/12 �}�N���ǉ�                                                       ��
//��ver.	1.02	2004/12/17 ��`�ǉ� �^�C�}�[��1Time�^�C�}�[�ǉ�                             ��
//��ver.	1.06	2005/01/09 ��`�ǉ� ���M���̑��M�|�[�g�w��ǉ�                              ��
//������������������������������������������������������������������������������������������������
#pragma once

//�֐��߂�l
#define	SDGDLL_RESULTOK			(0)					// CallBack�֐� OK
#define	SDGDLL_RESULTERROR		(1)					// CallBack�֐� NG
#define	SDGDLL_RESULTCANCEL		(2)					// CallBack�֐� (Cancel)

#define SDGDLL_CONFIGUSE		(1)					// Config�ݒ肠��
#define SDGDLL_CONFIGNOT		(0)					// Config���Ȃ�

#define SDGDLL_LOGINFO			(1)					// LOG INFO
#define SDGDLL_LOGEXCL			(2)					// LOG EXCL
#define SDGDLL_LOGERR			(3)					// LOG ERROR

#define SDGDLL_TIMER1			(0x00000000)		// Timer No.1
#define SDGDLL_TIMER2			(0x00000001)		// Timer No.2
#define SDGDLL_TIMER_1TIME		(0x80000000)		// �P�񂾂��L���̃^�C�}�[

//�v���p�����[�^�r�b�g(�C�x���g)
#define SDGDLL_ONCONNECT		(0x00000001)		// �ڑ�����
#define SDGDLL_ONCLOSE			(0x00000002)		// �ؒf
#define SDGDLL_ONRECEIVE		(0x00000004)		// �f�[�^��M
#define SDGDLL_ONSEND 			(0x00000008)		// �f�[�^���M�v��
#define SDGDLL_ONTIMER 			(0x00000010)		// �^�C�}�[�C�x���g

//�v���p�����[�^�r�b�g(�v���R�}���h)
#define SDGDLL_REQSEND			(0x00000100)		// ���M�v��
#define SDGDLL_REQCLOSE			(0x00000200)		// �ؒf�v��
#define SDGDLL_REQSTARTTIMER	(0x00000400)		// �^�C�}�[�C�x���g(�J�n)�v��
#define SDGDLL_REQSTOPTIMER		(0x00000800)		// �^�C�}�[�C�x���g(��~)�v��
#define SDGDLL_REQEDITER		(0x00001000)		// �G�f�B�^�f�[�^�擾�v��(�A���T�[�L��)
#define SDGDLL_REQSETEDITER		(0x00002000)		// �G�f�B�^�f�[�^�ݒ�v��

//�v���p�����[�^�r�b�g(���̑��C�x���g�Ȃ�)
#define SDGDLL_GETCOMMENT		(0x01000000)		// �R�����g�擾�v��
#define SDGDLL_GETVER			(0x02000000)		// Ver.�擾(�߂�l�ɂ��)
#define SDGDLL_CONFIGRESULT		(0x04000000)		// �R���t�B�O�ݒ肠��H
#define SDGDLL_EDITCONFIG		(0x08000000)		// �ݒ��ʕ\��
#define SDGDLL_SETCONFIG		(0x10000000)		// �ݒ�Z�b�g
#define SDGDLL_RECALL			(0x80000000)		// �R�}���h���s��ČĂяo���w��

//�f�[�^���M���w��
#define SDGDLL_SEND_ME			(0)					// �Ή������|�[�g�ő��M
#define SDGDLL_SEND_PORT1		(1)					// �|�[�g�P�i�S�āj�ő��M
#define SDGDLL_SEND_PORT2		(2)					// �|�[�g�Q�i�S�āj�ő��M
//---------------------------------------------------------------
//	CallBack �֐� �p�����[�^
//---------------------------------------------------------------
typedef struct {
	DWORD	command;	// �R�}���h
	DWORD	wparam;		// �p�����[�^(1)
	DWORD	lparam;		// �p�����[�^(2)
	DWORD	myWparam;	// DLL�����ŕK�v�Ƃ���f�[�^�̃p�����[�^(1)
	DWORD	myLparam;	// DLL�����ŕK�v�Ƃ���f�[�^�̃p�����[�^(2)

	DWORD	buffsize;	// �o�b�t�@�T�C�Y
	LPVOID	lpbuffer;	// �o�b�t�@�̐擪�A�h���X

	DWORD	logsize;	// ���O�o�̓o�b�t�@�T�C�Y
	DWORD	logtype;	// ���O�o�̓^�C�v 0:None 1:Info 2:Exclamation 3:Error
	LPVOID	logbuffer;	// ���O���b�Z�[�W
} SDGDLLSTRUCT;



/*
������������������������������������������������������
��                                                  ��
��            �R�[���o�b�N�֐��̒�`                ��
��                                                  ��
��                                                  ��
������������������������������������������������������
������������������������������������������������������
��DWORD WINAPI CallBackSDG( ULONG dest, ULONG src ) ��
������������������������������������������������������
��CallBack�֐��́ASDGDLLSTRUCT���Q�̗̈�擪�A�h���X��n����ăR�[�������B
�����p�����[�^(dest)
�����p�����[�^(src)
���Ƃ��Ĉ����Aexe����̎w����src�Ɋi�[�����B
��dll�ł́Adest�ɃA���T�[���i�[����B
���߂�l�͐�p�̒�`�ōs���B
��
������������������������������������������������������
��                                                  ��
��                 ���ʋ@�\���                     ��
��                                                  ��
��                                                  ��
������������������������������������������������������
������������������������������������������������������
���@RECALL                                          ��
������������������������������������������������������
��DLL�ŏ������s�������ƁA���̏������e��ADLL�̍\���ɂ��A
���G���A����Ȃǂ̃^�C�~���O���~�����ꍇ������B
�����̏ꍇ�Adest�R�}���h��SDGDLL_RECALL��t�^���邱�Ƃɂ������ł���B
���Ăяo�����������ƂȂ����R�}���h�t���O�Ɠ����ɗ��Ă邱�Ƃ𐄏�����B
���{�@�\��OK(Online���B���x�ł��w��\)�ƁA1 Time(1�x�����\�j�̏ꍇ�̂ݎw��\�B
��
������������������������������������������������������
���AMy Param                                        ��
������������������������������������������������������
��myWparam	DLL�����ŋL�����Ă����������l�i�A�h���X�j��ۑ�����B
��myLparam	DLL�����ŋL�����Ă����������l�i�A�h���X�j��ۑ�����B
��DLL�̓R�[���o�b�N�ŋN������邽�߁A�Ăяo���̑O��Ŋ֌W�����ĂȂ��B
���������A�A�������������s�����߂ɂ͏������Ƃ̋L���G���A���K�v�ƂȂ�B
�����̂��߁Adest�ɖ{�f�[�^���Z�b�g���Ă������Ƃɂ��
�����̃C�x���g����src�ɒl���R�s�[����N�������B
������𗘗p���āA�����̃V�[�P���X�̍쐬���\�ƂȂ�B
���{�@�\���w��ł�����̂�
��My Param OK
���ƂȂ��Ă���C�x���g�A�R�}���h�ł���B
��
������������������������������������������������������
���B���O�@�\                                        ��
������������������������������������������������������
��Online����DLL������R�����g����ʂɏo�͂��邱�Ƃ��o����B
��Log OK 
���ƂȂ��Ă���R�}���h�A�C�x���g���Ή��B
��
��src��
��logsize   : ���O�o�̓o�b�t�@�T�C�Y (0�łȂ�����)
��logbuffer	: ���O�o�̓A�h���X       (NULL�łȂ�����)
����L�A()���̏������������ꂽ�Ăяo���̏ꍇ�A���O�o�͉\�ł���B
��
�����O�o�͂̎菇
��1.src��logbuffer�A�h���X��dest��logbuffer�ɒl�R�s�[
��2.logbuffer�A�h���X��src��logsize��(NULL�͍l�����邱��)�Ƀ��O�������Z�b�g
��3.dest��logtype�Ƀ^�C�v���Z�b�g
�� 1:���
�� 2:����
�� 3:�x��
��
������������������������������������������������������
���COnline����                                      ��
������������������������������������������������������
��Online���ʎd�l�Ƃ��Đݒ�\��dest��command�p�����[�^�������B
��
��SDGDLL_REQSEND
��SDGDLL_REQCLOSE	(���̎w��̏ꍇ�ASDGDLL_RECALL�͐ݒ�ł��Ȃ��B���ɔ�������C�x���g��SDGDLL_ONCLOSE�ł���B�j
��SDGDLL_REQSTARTTIMER
��SDGDLL_REQSTOPTIMER
��SDGDLL_REQEDITER�iSDGDLL_RECALL�w��͕s�v�Bdest�Ŏw����ɁAsrc��SDGDLL_REQEDITER�C�x���g����������B�j
��SDGDLL_REQSETEDITER
��Online���́A�����̃R�}���h�����s�ł���B
���e�R�}���h�͓����ݒ�͍s���Ȃ��B
�����L�̂Ȃ����̂�SDGDLL_RECALL���`�ł���B
���ڍׂ́A���ɋL�q����B
��
������������������������������������������������������
��                                                  ��
��                 �C�x���g����                     ��
��                  EXE --> DLL                     ��
��                                                  ��
������������������������������������������������������
������������������������������������������������������
��                 �R�����g�擾                     ��
������������������������������������������������������
��	SDGDLL_GETCOMMENT
����������������������������������������������������
��	Scene.		Config
��	RECALL		No
��	My Param	No
��	Log			No
��	Return		SDGDLL_RESULTOK
����������������������������������������������������
��	src:
��		command		(SDGDLL_GETCOMMENT)
��		wparam		0:�^�C�g�� 1:����
��	dest:
��		buffsize	:	NULL���܂񂾕�����
��		lpbuffer	:	�������擪�A�h���X
����������������������������������������������������
��	DLL�̐�������Ԃ��B
��	�����Ŏg�p����o�b�t�@�͉�����ł��Ȃ��̂�
��	DLL������static�錾���Ă������ƁB
��	(���̂��߁A���̕������DLL���Ƃɕs�ςƂȂ�B)
������������������������������������������������������
��                 �^�C�v�擾                       ��
������������������������������������������������������
��	SDGDLL_GETVER
����������������������������������������������������
��	Scene. 		Config, Online(before)
��	RECALL 		No
��	My Param	No
��	Log			No
��	Return		SDGDLL_RESULTOK
����������������������������������������������������
��	src:
��		command		(SDGDLL_GETVER)
��	dest:
��		wparam		:	�^�C�v�ԍ�
����������������������������������������������������
��	DLL�̃^�C�v��Ԃ��B
��	����A�Ή��́A0x100�݂̂ł���B
��	�i�����A�g�������̒ǉ����ɑΉ��^�C�v�Ƃ��ĕԂ��\��j
��	DLL�̑I����ʂŕ\������ق��A
��	Online�J�n�O�ɂ��m�F�̂��߃R�[�������B
������������������������������������������������������
��               �ڍאݒ�\���m�F                 ��
������������������������������������������������������
��	SDGDLL_CONFIGRESULT
����������������������������������������������������
��	Scene. 		Config, Online(before)
��	RECALL 		No
��	My Param	No
��	Log			No
��	Return		SDGDLL_RESULTOK
����������������������������������������������������
��	src:
��		command		(SDGDLL_CONFIGRESULT)
��	dest:
��		wparam		:	SDGDLL_CONFIGNOT:�Ȃ�   SDGDLL_CONFIGUSE:�L��
����������������������������������������������������
��	���̊g�������ɏڍאݒ�f�[�^�E�B���h�E�����邩�`�F�b�N����B
��	DLL�I����ʂŁu�ڍ׏��v�{�^���������邩�̃`�F�b�N��
��	Online�O�ɐݒ肳�ꂽ�f�[�^��DLL�ɓn���K�v�����邩���`�F�b�N����B
��	�{������L��Ƃ����ꍇ�A�ڍאݒ�E�B���h�E�v��������
��	�Ή�����K�v������B
������������������������������������������������������
��                  �ڍאݒ�v��                    ��
������������������������������������������������������
��	SDGDLL_EDITCONFIG
����������������������������������������������������
��	Scene. 		Config
��	RECALL		1 Time
��	My Param	No
��	Log			No
��	Return		SDGDLL_RESULTOK, SDGDLL_RESULTCANCEL
����������������������������������������������������
��	src:
��		command		(SDGDLL_EDITCONFIG)
��		lpbuffer	:	���ɕҏW���ꂽ�ݒ�f�[�^������ꍇ�݂̂��̃f�[�^�̐擪�A�h���X���i�[�����B
��		buffsize	:	�f�[�^�o�b�t�@�̃T�C�Y�B�ݒ肪�Ȃ��ꍇ��0���i�[�����B
��	dest:
��		command		(SDGDLL_EDITCONFIG | SDGDLL_RECALL)
��					�������Ńo�b�t�@�m�ۂ��ĕԑ������ꍇ�́A���̃G���A����̂��߂ɍs���K�v������B
��					�@�o�b�t�@�m�ۂ��Ȃ����0�ł��܂�Ȃ�
��		lpbuffer	:	�ڍאݒ�ō쐬�����f�[�^���o�C�g�z��Ƃ��Ĉ����B���̐擪�A�h���X
��		buffsize	:	�ڍאݒ�f�[�^�o�C�g��
����������������������������������������������������
��	DLL�I����ʂ���u�ڍ׏��v�{�^�������ŃR�[�������B
��	DLL�����Őݒ�E�B���h�E���J���A���[�U�Ƀf�[�^�o�^��񋟂���B
��	�ݒ肳�ꂽ�f�[�^��exe�ɓn�����ƂŁA�ʐM�ݒ���ƈꏏ�Ƀt�@�C���ۑ����\�ƂȂ�B
��	�����Őݒ肵���f�[�^��Online�O�ɍĂсADLL�Ƀf�[�^���������̂�
��	�ݒ�f�[�^�ɏ]�����ʐM�������\�ƂȂ�B
��	�ݒ�f�[�^��exe�ɕԋp���邽�߂Ɉꎞ�I�Ƀo�b�t�@���m�ۂ���K�v������B
��	���̏ꍇ�A��������̂��߂�1�x����SDGDLL_RECALL�ɂ��
��	�ČĂяo���w����\�Ƃ���B
������������������������������������������������������
��               �ݒ�f�[�^�̓���                   ��
������������������������������������������������������
��	SDGDLL_SETCONFIG
����������������������������������������������������
��	Scene. 		Online(before)
��	RECALL 		No
��	My Param	OK (dest�ŕԂ��ꂽ���̂��炪�Ώ�)
��	Log			OK
��	Return		SDGDLL_RESULTOK, SDGDLL_RESULTERROR
����������������������������������������������������
��	src:
��		command		(SDGDLL_SETCONFIG)
��		lpbuffer	:	�ҏW���ꂽ�ݒ�f�[�^������ꍇ�݂̂��̃f�[�^�̐擪�A�h���X���i�[�����B
��		buffsize	:	�f�[�^�o�b�t�@�̃T�C�Y�B�ݒ肪�Ȃ��ꍇ��0���i�[�����B
��		logsize;	:	(Log�@�\�ɂ��)
��		logtype;	:	(Log�@�\�ɂ��)
��		logbuffer;	:	(Log�@�\�ɂ��)
��	dest:
��		myWparam	:	(My Param�@�\�ɂ��)
��		myLparam	:	(My Param�@�\�ɂ��)
��		logsize;	:	(Log�@�\�ɂ��)
��		logtype;	:	(Log�@�\�ɂ��)
��		logbuffer;	:	(Log�@�\�ɂ��)
����������������������������������������������������
��	DLL�̐ݒ�E�B���h�E�Œ�`���ꂽ�ݒ����DLL�Ɉ����n���B
��	�{�����ȍ~�AOnline�������J�n����邽��
��	DLL�����Ńf�[�^��ۑ����Ă������ƁB
��	My Param�@�\�͂��̏�����dest����L���ƂȂ�B
��	�f�[�^�̉����SDGDLL_ONCLOSE�ōs���B�iDLL�I���̃C�x���g)
������������������������������������������������������
��                  �ʐM�����J�n                    ��
������������������������������������������������������
��	SDGDLL_ONCONNECT
����������������������������������������������������
��	Scene. 		Online
��	RECALL 		OK
��	My Param	OK
��	Log			OK
��	Return		SDGDLL_RESULTOK, SDGDLL_RESULTERROR
����������������������������������������������������
��	src:
��		command		(SDGDLL_ONCONNECT)
��		myWparam	:	(My Param�@�\�ɂ��)
��		myLparam	:	(My Param�@�\�ɂ��)
��		logsize;	:	(Log�@�\�ɂ��)
��		logtype;	:	(Log�@�\�ɂ��)
��		logbuffer;	:	(Log�@�\�ɂ��)
��	dest:
��		command		:	(Online����)
��		myWparam	:	(My Param�@�\�ɂ��)
��		myLparam	:	(My Param�@�\�ɂ��)
��		logsize;	:	(Log�@�\�ɂ��)
��		logtype;	:	(Log�@�\�ɂ��)
��		logbuffer;	:	(Log�@�\�ɂ��)
����������������������������������������������������
��	�\�P�b�g�����J�n���ɃR�[�������B
��	�^�C�}�[��A���M�����Ȃǂ̃R�}���h��Ƃ�
��	�{�C�x���g����\�ƂȂ�B
������������������������������������������������������
��                  �f�[�^��M                      ��
������������������������������������������������������
��	SDGDLL_ONRECEIVE
����������������������������������������������������
��	Scene. 		Online
��  RECALL 		OK
��	My Param	OK
��	Log			OK
��	Return		SDGDLL_RESULTOK, SDGDLL_RESULTERROR
����������������������������������������������������
��	src:
��		command		(SDGDLL_ONRECEIVE)
��		lpbuffer	:	��M�f�[�^�擪�A�h���X
��		buffsize	:	��M�����o�C�g��
��		myWparam	:	(My Param�@�\�ɂ��)
��		myLparam	:	(My Param�@�\�ɂ��)
��		logsize;	:	(Log�@�\�ɂ��)
��		logtype;	:	(Log�@�\�ɂ��)
��		logbuffer;	:	(Log�@�\�ɂ��)
��	dest:
��		command		:	(Online����)
��		myWparam	:	(My Param�@�\�ɂ��)
��		myLparam	:	(My Param�@�\�ɂ��)
��		logsize;	:	(Log�@�\�ɂ��)
��		logtype;	:	(Log�@�\�ɂ��)
��		logbuffer;	:	(Log�@�\�ɂ��)
����������������������������������������������������
��	�\�P�b�g�Ńf�[�^����M�����ۂɃf�[�^�ƂƂ��ɃR�[�������B
��	�ԐM�f�[�^������΁Adest��command��SDGDLL_REQSEND�Ȃǂ�
��	�t���Ă��̌�̏������s���B
��	���ɏ������������dest��command��0��Ԃ��݂̂ł悢�B
������������������������������������������������������
��          ���M�f�[�^�G�f�B�^�f�[�^�̒ʒm          ��
������������������������������������������������������
��	SDGDLL_REQEDITER
����������������������������������������������������
��	Scene. 		Online
��  RECALL 		OK
��	My Param	OK
��	Log			OK
��	Return		SDGDLL_RESULTOK, SDGDLL_RESULTERROR
����������������������������������������������������
��	src:
��		command		(SDGDLL_REQEDITER)
��		lpbuffer	:	���M�f�[�^�G�f�B�^�f�[�^�擪�A�h���X
��		buffsize	:	���M�f�[�^�G�f�B�^�f�[�^�o�C�g��
��		myWparam	:	(My Param�@�\�ɂ��)
��		myLparam	:	(My Param�@�\�ɂ��)
��		logsize;	:	(Log�@�\�ɂ��)
��		logtype;	:	(Log�@�\�ɂ��)
��		logbuffer;	:	(Log�@�\�ɂ��)
��	dest:
��		command		:	(Online����)
��		myWparam	:	(My Param�@�\�ɂ��)
��		myLparam	:	(My Param�@�\�ɂ��)
��		logsize;	:	(Log�@�\�ɂ��)
��		logtype;	:	(Log�@�\�ɂ��)
��		logbuffer;	:	(Log�@�\�ɂ��)
����������������������������������������������������
��	�{�����́A�l�b�g���[�N�C�x���g�ŋN���������̂ł͂Ȃ��B
��	dest�w����SDGDLL_REQEDITER(���M�f�[�^�G�f�B�^���̃f�[�^�v��)���s�����ꍇ
��	�f�[�^���e��ʒm���邽�߂ɃR�[������B
������������������������������������������������������
��                    �^�C�}�[�ʒm                  ��
������������������������������������������������������
��	SDGDLL_ONTIMER
����������������������������������������������������
��	Scene. 		Online
��  RECALL 		OK
��	My Param	OK
��	Log			OK
��	Return		SDGDLL_RESULTOK, SDGDLL_RESULTERROR
����������������������������������������������������
��	src:
��		command		(SDGDLL_ONTIMER)
��		wparam		:	�^�C�}�[ID�@�i0 or 1)
��		myWparam	:	(My Param�@�\�ɂ��)
��		myLparam	:	(My Param�@�\�ɂ��)
��		logsize;	:	(Log�@�\�ɂ��)
��		logtype;	:	(Log�@�\�ɂ��)
��		logbuffer;	:	(Log�@�\�ɂ��)
��	dest:
��		command		:	(Online����)
��		myWparam	:	(My Param�@�\�ɂ��)
��		myLparam	:	(My Param�@�\�ɂ��)
��		logsize;	:	(Log�@�\�ɂ��)
��		logtype;	:	(Log�@�\�ɂ��)
��		logbuffer;	:	(Log�@�\�ɂ��)
����������������������������������������������������
��	�ݒ肵���^�C�}�[�����ԂɂȂ����ۂɃR�[�������B
��	���M�f�[�^������΁Adest��command��SDGDLL_REQSEND�Ȃǂ�
��	�t���Ă��̌�̏������s�����肷��B
������������������������������������������������������
��                 �\�P�b�g�����I��                 ��
������������������������������������������������������
��	SDGDLL_ONCLOSE
����������������������������������������������������
��	Scene. 		Online
��  RECALL 		OK
��	My Param	OK
��	Log			OK
��	Return		SDGDLL_RESULTOK, SDGDLL_RESULTERROR
����������������������������������������������������
��	src:
��		command		(SDGDLL_ONCLOSE)
��		myWparam	:	(My Param�@�\�ɂ��)
��		myLparam	:	(My Param�@�\�ɂ��)
��		logsize;	:	(Log�@�\�ɂ��)
��		logtype;	:	(Log�@�\�ɂ��)
��		logbuffer;	:	(Log�@�\�ɂ��)
��	dest:
��		command		:	�ݒ�s��
��		myWparam	:	�ݒ�s��
��		myLparam	:	�ݒ�s��
��		logsize;	:	(Log�@�\�ɂ��)
��		logtype;	:	(Log�@�\�ɂ��)
��		logbuffer;	:	(Log�@�\�ɂ��)
����������������������������������������������������
��	�\�P�b�g�����̏I�����ɃR�[�������B
��	������ʂ��čŌ�̃R�[���ƂȂ�̂ŉ������
��	�f�[�^��������΂����ŕK��������s���B
������������������������������������������������������
��                                                  ��
��                  Online������                    ��
��    Online���� DLL -> EXE�ɑ΂��čs�������v��     ��
��                                                  ��
������������������������������������������������������
������������������������������������������������������
��                 �f�[�^���M�v��                   ��
������������������������������������������������������
��	SDGDLL_REQSEND
����������������������������������������������������
��	Scene. 		Online
��  RECALL 		OK
��	My Param	OK
��	Log			OK
��	Return		SDGDLL_RESULTOK, SDGDLL_RESULTERROR
����������������������������������������������������
��	dest:
��		command		:	SDGDLL_REQSEND | SDGDLL_RECALL(OPTION)
��		lpbuffer	:	���M�f�[�^�擪�A�h���X
��		buffsize	:	���M����o�C�g��
��		wparam		:	���M�f�[�^�|�[�g�w��
��						SDGDLL_SEND_ME		(�Ή������|�[�g�ő��M)
��						SDGDLL_SEND_PORT1	(�|�[�g�P�i�S�āj�ő��M)
��						SDGDLL_SEND_PORT2	(�|�[�g�Q�i�S�āj�ő��M)
��		(���̑��p�����[�^�́A�e�C�x���g��dest�ɏ�����B)
����������������������������������������������������
��	�f�[�^�̑��M�v�����s���B
��	���̏����̑�����DLL�����ŃG���A�m�ۂ��s���Ǝv���̂�
��	���̏ꍇ��SDGDLL_RECALL��t���āA
��	�ăR�[�����āA�G���A�̉�����s���K�v������B
��	�G���A���m�ۂ��Ă��Ȃ�������A
��	SDGDLL_ONCLOSE�ŉ������ꍇ�͂��̌���łȂ��B
��	�n���ꂽ�f�[�^�͂������܃R�s�[����A�Ȍ�A�n���ꂽ
��	�f�[�^�A�h���X�ɃA�N�Z�X���邱�Ƃ͂Ȃ��B
������������������������������������������������������
��                �ʐM�����I���v��                  ��
������������������������������������������������������
��	SDGDLL_REQCLOSE
����������������������������������������������������
��	Scene. 		Online
��  RECALL 		No
��	My Param	OK
��	Log			OK
��	Return		SDGDLL_RESULTOK, SDGDLL_RESULTERROR
����������������������������������������������������
��	dest:
��		command		:	SDGDLL_REQCLOSE
��		(���̑��p�����[�^�́A�e�C�x���g��dest�ɏ�����B)
����������������������������������������������������
��	�ʐM�̏I����v������B
��	�R�}���h���s��ASDGDLL_ONCLOSE�C�x���g����������̂�
��	�G���A����Ȃǂ͂�����ōs�����Ƃ��]�܂����B
������������������������������������������������������
��                �^�C�}�[�J�n�v��                  ��
������������������������������������������������������
��	SDGDLL_REQSTARTTIMER
����������������������������������������������������
��	Scene. 		Online
��  RECALL 		OK
��	My Param	OK
��	Log			OK
��	Return		SDGDLL_RESULTOK, SDGDLL_RESULTERROR
����������������������������������������������������
��	dest:
��		command		:	SDGDLL_REQSTARTTIMER | SDGDLL_RECALL(OPTION)
��		wparam		:	�^�C�}�[ID ( SDGDLL_TIMER1 or SDGDLL_TIMER2 )
��                      (SDGDLL_TIMER_1TIME �Ƒg�ݍ��킹���1�񂵂��C�x���g���s���Ȃ��B
��                       ����ȊO�͘A���Ŏ������s�����)
��		lparam		:	�^�C�}�[����( �~��sec )
��		(���̑��p�����[�^�́A�e�C�x���g��dest�ɏ�����B)
����������������������������������������������������
��	�^�C�}�[������v������B
��	�ݒ�\�ȃ^�C�}�[�͂Q�܂ŁB
��  SDGDLL_TIMER_1TIME�Ƒg�ݍ��킹��ƂP��̂݃C�x���g���s���A
��  �^�C�}�[�͎�����~����B
��	�蓮�^�C�}�[��~�́ASDGDLL_REQSTOPTIMER�v���ōs���B
��	�ʐM�����I�����͎�����~�����B
��	�^�C�}�[�C�x���g�̒ʒm��SDGDLL_ONTIMER�ōs����B
������������������������������������������������������
��                �^�C�}�[��~�v��                  ��
������������������������������������������������������
��	SDGDLL_REQSTOPTIMER
����������������������������������������������������
��	Scene. 		Online
��  RECALL 		OK
��	My Param	OK
��	Log			OK
��	Return		SDGDLL_RESULTOK, SDGDLL_RESULTERROR
����������������������������������������������������
��	dest:
��		command		:	SDGDLL_REQSTOPTIMER | SDGDLL_RECALL(OPTION)
��		wparam		:	�^�C�}�[ID ( 0 or 1 )
��		(���̑��p�����[�^�́A�e�C�x���g��dest�ɏ�����B)
����������������������������������������������������
��	�^�C�}�[�������~����B
��	�^�C�}�[���ݒ肳��Ă��Ȃ��ꍇ�͉����������s��Ȃ��B
������������������������������������������������������
��            ���M�f�[�^�G�f�B�^�f�[�^�v��          ��
������������������������������������������������������
��	SDGDLL_REQEDITER
����������������������������������������������������
��	Scene. 		Online
��  RECALL 		NG(�ݒ肵�Ȃ��Ƃ��A���T�[�C�x���g����������B)
��	My Param	OK
��	Log			OK
��	Return		SDGDLL_RESULTOK, SDGDLL_RESULTERROR
����������������������������������������������������
��	dest:
��		command		:	SDGDLL_REQEDITER
��		(���̑��p�����[�^�́A�e�C�x���g��dest�ɏ�����B)
����������������������������������������������������
��	���M�f�[�^�G�f�B�^�ɃZ�b�g����Ă������v������B
��	�A���T�[�Ƃ���SDGDLL_REQEDITER���C�x���g�Ŕ�������B
������������������������������������������������������
��       ���M�f�[�^�G�f�B�^�Ƀf�[�^�Z�b�g�v��       ��
������������������������������������������������������
��	SDGDLL_REQSETEDITER
����������������������������������������������������
��	Scene. 		Online
��  RECALL 		OK
��	My Param	OK
��	Log			OK
��	Return		SDGDLL_RESULTOK, SDGDLL_RESULTERROR
����������������������������������������������������
��	dest:
��		command		:	SDGDLL_REQSETEDITER | SDGDLL_RECALL(OPTION)
��		lpbuffer	:	�Z�b�g�f�[�^�擪�A�h���X
��		buffsize	:	�Z�b�g����o�C�g��
��		(���̑��p�����[�^�́A�e�C�x���g��dest�ɏ�����B)
����������������������������������������������������
��	���M�f�[�^�G�f�B�^�Ɏw�肵���f�[�^���Z�b�g����B
��	�G���A����̂��߂�SDGDLL_RECALL���s���B�i�K�v�Ȃ�΁j
������������������������������������������������������
��                                                  ��
��              �ăR�[���ɂ���                    ��
��                                                  ��
��                                                  ��
������������������������������������������������������
��SDGDLL_RECALL���Z�b�g�����ꍇ�A�����͌��ƂȂ���
���C�x���g�i�R�}���h�j�ƃZ�b�g�Ŏw�肷��B
�������̏�������DLL�����ł͑Ή��������L�q����B
���������ASDGDLL_RECALL�P�Ƃł̃Z�b�g���\�ł���B
�����̏ꍇ��My Param�@�\���g����DLL�����̏����󋵂�c�����čs���ė~�����B


*/



/*
������������������������������������������������������
��                                                  ��
��              �쐬�x���}�N��                      ��
��                                                  ��
��                                                  ��
������������������������������������������������������
*/
//####################################################################
//	����:	�O���[�o���錾�}�N��
//	�@�\:
//####################################################################
#define MC_SDGHEAD( xxx1,xxx2 )			\
static char sdg_mc1[] = xxx1;			\
static char sdg_mc2[] = xxx2;
//####################################################################
//	����:	���O�̏o�̓T�u���[�`���}�N��
//	�@�\:
//####################################################################
#define MC_SDGMODULE																			\
	void SDGLogWrite( SDGDLLSTRUCT* dest, SDGDLLSTRUCT* src, int info, const char* comment )	\
	{																							\
		if( src->logbuffer == NULL )					return;									\
		if( src->logsize <= (DWORD)lstrlen(comment) )	return;									\
		dest->logbuffer = src->logbuffer;														\
		dest->logtype = info;																	\
		lstrcpy( (char*)dest->logbuffer, comment );												\
	}
//####################################################################
//	����:	�}�N���g�p���̐錾
//	�@�\:
//####################################################################
#define MC_MODULEUSE										\
	SDGDLLSTRUCT*	destData	= (SDGDLLSTRUCT*)dest;		\
	SDGDLLSTRUCT*	srcData		= (SDGDLLSTRUCT*)src;
//####################################################################
//	����:	�ԐM�̂��߂̊�{����
//	�@�\:
//####################################################################
#define MC_EV_DEFAULT										\
	destData->command = NULL;								\
	destData->myWparam = srcData->myWparam;					\
	destData->myLparam = srcData->myLparam;
//####################################################################
//	����:	(Event) �R�����g�ԑ��}�N��
//	�@�\:
//####################################################################
#define MC_EV_GETCOMMENT									\
	if( srcData->command & SDGDLL_GETCOMMENT ){				\
		if( srcData->wparam == 0 ){							\
			destData->buffsize = lstrlen( sdg_mc1 )+1;		\
			destData->lpbuffer = sdg_mc1;					\
		}													\
		else{												\
			destData->buffsize = lstrlen( sdg_mc2 )+1;		\
			destData->lpbuffer = sdg_mc2;					\
		}													\
		return SDGDLL_RESULTOK;								\
	}
//####################################################################
//	����:	(Event) �o�[�W�����ԑ��}�N��
//	�@�\:
//####################################################################
#define MC_EV_GETVER										\
	if( srcData->command & SDGDLL_GETVER ){					\
		destData->wparam = SDGDLL_VER;						\
		return SDGDLL_RESULTOK;								\
	}
//####################################################################
//	����:	(Event) �R���t�B�O�L���}�N��
//	�@�\:
//####################################################################
#define MC_EV_CONFIGRESULT(xxx)								\
	if( srcData->command & SDGDLL_CONFIGRESULT ){			\
		destData->wparam = xxx;								\
		return SDGDLL_RESULTOK;								\
	}
//####################################################################
//	����:	(Event) �R���t�B�O�ݒ��A�G���A����}�N��
//	�@�\:
//####################################################################
#define MC_EV_CONFIGFREE	{									\
	if( (srcData->command & SDGDLL_RECALL) && (srcData->command & SDGDLL_EDITCONFIG) ){	\
		if( srcData->lpbuffer != NULL ){						\
			GlobalFree( (HGLOBAL)srcData->lpbuffer );			\
		}														\
		return SDGDLL_RESULTOK;									\
	}															\
}
//####################################################################
//	����:	�R���t�B�O�ݒ莞�̗̈�m�ۃ}�N��
//	�@�\:	(COleSafeArray -> GlobalAlloc)
//####################################################################
#define MC_CONFIGALLOC( xxxx ){	\
	int		mcsize = xxxx.GetOneDimSize();						\
	char	*lpmcbyte;											\
	destData->buffsize = mcsize;								\
	destData->lpbuffer = (LPVOID)GlobalAlloc( GPTR, mcsize );	\
	xxxx.AccessData( (void**)&lpmcbyte );						\
	CopyMemory( destData->lpbuffer, lpmcbyte, mcsize );			\
	xxxx.UnaccessData();										\
}





