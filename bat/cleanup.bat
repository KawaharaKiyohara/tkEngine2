@echo on
@rem �N���[���A�b�v
@setlocal
@set CURRENT_DIR=%~dp0
pushd %CURRENT_DIR%

call .\Sample\cleanup.bat


@del "c:\Program Files\Autodesk\3ds Max 2015\scripts\tkExporter.ms"
@del "c:\Program Files\Autodesk\3ds Max 2016\scripts\tkExporter.ms"
@del "c:\Program Files\Autodesk\3ds Max 2017\scripts\tkExporter.ms"

popd

@echo �N���[���A�b�v�I��
