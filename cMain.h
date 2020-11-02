#pragma once
#include "wx/wx.h"
#include "wx/notebook.h"
#include "convolution_layer.h"
#include "InputFile.h"
#include <future>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include "NEAT.h"
enum type {
	training, testing
};
class cMain;
static bool isLanjut = false;
static bool isLanjutNEAT = false;
class MyThread : public wxThread
{
public:
	MyThread(cMain *handler, convolution_layer *CNN, type tipe)
		: wxThread(wxTHREAD_DETACHED)
	{
		m_pHandler = handler;
		this->CNN = CNN;
		this->tipe = tipe;
		epoch = 0;
		isRunning = false;
		this->tipe = tipe;

	}
	type tipe;
	bool isRunning;
	//~MyThread();
protected:
	void* Entry();
	unsigned short int epoch;
	cMain *m_pHandler;
	convolution_layer *CNN;
};

class ThreadNEAT : public wxThread {
public:
	ThreadNEAT(cMain *handler, type tipe)
		: wxThread(wxTHREAD_DETACHED)
	{
		m_pHandler = handler;
		this->tipe = tipe;
		generation = 0;
	}
	//~MyThread();
protected:
	void* Entry();
	type tipe;
	unsigned short int generation;
	cMain *m_pHandler;
};


class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
	void TextEntered(wxCommandEvent &event);
	void ButtonStartClicked(wxCommandEvent &event);
	void Button2Clicked(wxCommandEvent &event);
	void ComboSelected(wxCommandEvent &event);
	void ButtonLoadClicked(wxCommandEvent &event);
	void ButtonSaveClicked(wxCommandEvent &event);
	void ButtonLoadTestData1ClassClicked(wxCommandEvent &event);
	void ButtonLoadTestDataClicked(wxCommandEvent &event);
	void ButtonTestClicked(wxCommandEvent &event);
	void ButtonAddLayerClicked(wxCommandEvent &event);
	void ButtonLoadTrainDataClicked(wxCommandEvent &event);
	void ButtonClearTrainDataClicked(wxCommandEvent &event);
	void ButtonClearTestDataClicked(wxCommandEvent &event);
	void ButtonSetLearningRateClicked(wxCommandEvent &event);
	void buttonResetLayer(wxCommandEvent &event);
	void buttonPredict(wxCommandEvent &event);
	void load();
	const InputFile &getInputTrainConst() const { return in; };
	const InputFile &getInputTest() const { return in2; };
	InputFile &getInputTrain() { return in; };


	//NEAT
	void buttonLoadClickedNEAT(wxCommandEvent &event);
	void buttonSaveClickedNEAT(wxCommandEvent &event);
	void buttonTrainClickedNEAT(wxCommandEvent &event);
	void buttonTestClickedNEAT(wxCommandEvent &event);
	void buttonLoadTrainDataClickedNEAT(wxCommandEvent &event);
	void buttonLoadValidationDataClickedNEAT(wxCommandEvent &event);
	void buttonLoadTestDataClickedNEAT(wxCommandEvent &event);
	void buttonLoadTest1ClassDataClickedNEAT(wxCommandEvent &event);
	void buttonSetLearningRateClickedNEAT(wxCommandEvent &event);
	void buttonSetStructureClickedNEAT(wxCommandEvent &event);
	void buttonTextOutputNEAT(wxCommandEvent &event);
	void buttonClearTestDataNEATClicked(wxCommandEvent &event);
	void buttonResetStructureClicked(wxCommandEvent &event);
	void buttonPredictNEAT(wxCommandEvent &event);
private:
	friend class MyThread;
	friend class ThreadNEAT;
	MyThread *m_pThread;
	wxButton *btnStart = nullptr;
	wxButton *btnTest = nullptr;
	wxTextCtrl *text = nullptr;
	wxPanel *panel = nullptr;
	wxPanel *panel2 = nullptr;
	convolution_layer *CNN = nullptr;
	wxComboBox *combo;
	wxButton *newBut;
	wxButton *loadTrainData;
	wxButton *newBut2;
	wxButton *TestData;
	wxButton *loadTestData1class;
	wxButton *loadFile;
	wxButton *saveFile;
	wxButton *resetLayer;
	wxButton *predict;
	wxTextCtrl *text2;
	wxTextCtrl *text3;
	wxButton *buttonClearTrainData;
	wxButton *buttonClearTestData;
	wxButton *buttonAddLayer;
	wxButton *buttonSetLearningRate;
	wxTextCtrl *textLearningRate;
	wxStaticText *sTextFilterSize;
	wxStaticText *sTextOut;
	wxTextCtrl *sText1Class;
	wxTextCtrl * filterSizeText;
	wxTextCtrl * out;
	wxBoxSizer *sizer3;
	InputFile in;
	InputFile in2;

	//NEAT
	NEAT *neat = nullptr;
	ThreadNEAT *thd_NEAT = nullptr;
	PrepareInput train;
	PrepareInput validation;
	PrepareInput test;
	wxButton *buttonTestNEAT;
	wxButton *buttonTrainNEAT;
	wxButton *buttonLoadTrainDataNEAT;
	wxButton *buttonLoadValidationDataNEAT;
	wxButton *buttonLoadTestDataNEAT;
	wxButton *butonLoadTest1ClassDataNEAT;
	wxButton *buttonSetLearningRateNEAT;
	wxButton *buttonSetStructureNEAT;
	wxButton *buttonLoadNEAT;
	wxButton *buttonSaveNEAT;
	wxButton *buttonClearTestDataNEAT;
	wxButton *buttonResetStructure;
	wxButton *predictNEAT;
	wxTextCtrl *text1ClassNEAT;
	wxTextCtrl *textSetLearningRateNEAT;
	wxTextCtrl *textNumInputNEAT;
	wxTextCtrl *textNumHiddenNEAT;
	wxTextCtrl *textNumOutputNEAT;
	wxTextCtrl *textNumPopulationNEAT;
	wxStaticText *sText1ClassNEAT;
	wxStaticText *sTextSetLearningRateNEAT;
	wxStaticText *sTextSetStructure;
	wxStaticText *sTextNumInputNEAT;
	wxStaticText *sTextNumHiddenNEAT;
	wxStaticText *sTextNumOutputNEAT;
	wxStaticText *sTextNumPopulationNEAT;
	wxTextCtrl *outputNEAT;


};

