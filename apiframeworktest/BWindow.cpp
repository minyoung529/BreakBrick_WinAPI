#include "pch.h"
#include "BWindow.h"
#include "Core.h"
#include "Resource.h"
#include "KeyMgr.h"
BWindow::BWindow() : m_hWnd(0), m_hInstance(0)
{
}

BWindow::~BWindow()
{
}

LRESULT BWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0); // WM_QUIT
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}
int BWindow::Run(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	m_hInstance = hInstance;
	this->MyRegisterClass();
	this->WindowCreate();
	this->WindowShow(nCmdShow);
	this->WindowUpdate();

	// Core �ʱ�ȭ
	if (FAILED(Core::GetInst()->Init(m_hWnd, POINT{ SCREEN_X, SCREEN_Y })))
	{
		MessageBox(nullptr, L"Core ��ü �ʱ�ȭ ����", L"ERROR", MB_OK);
		return FALSE;
	}
	return this->MessageLoop(); // ���⼭ ���ѷ���. ������ ���α׷� ����(exitcode�� �԰�)
}

ATOM BWindow::MyRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = BWindow::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = LoadIcon(m_hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = WINDOW_NAME;
	wcex.hIconSm = LoadIcon(m_hInstance, IDI_APPLICATION);

	return RegisterClassExW(&wcex);
}

void BWindow::WindowCreate()
{
	m_hWnd = CreateWindowW(WINDOW_NAME, L"�������� ���ѿ�!", /*WS_POPUPWINDOW*/WS_OVERLAPPEDWINDOW,
		0, 0, SCREEN_X, SCREEN_Y, nullptr, nullptr, m_hInstance, nullptr);
}

void BWindow::WindowShow(int nCmdShow)
{
	ShowWindow(m_hWnd, nCmdShow);
}

void BWindow::WindowUpdate()
{
	UpdateWindow(m_hWnd);
}

int BWindow::MessageLoop()
{
	MSG msg;
	memset(&msg, 0, sizeof(msg));
	// PeekMessage
	while (true)
	{
		// �޽����� ������ ����
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// �츮�� ���� ������ ���ž�.
		else
		{
			if (Core::GetInst()->GetGameOver())
			{
				break;
			}

			// "������ ��������."
			Core::GetInst()->Progress();
		}
	}

	return (int)msg.wParam;
}