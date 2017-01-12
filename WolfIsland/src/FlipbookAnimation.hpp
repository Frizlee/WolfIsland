#pragma once
#include "Prerequisites.hpp"


/// <summary>	Klasa reprezentujaca animację typu flipbook. </summary>
class FlipbookAnimation
{
public:
	/// <summary>	Domyślny konstruktor. </summary>
	FlipbookAnimation();

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	/// 	Konstruktor tworzący animację z podanego zbioru spriteów oraz kolejnych klatek 
	/// 	animacji.  
	/// </summary>
	///
	/// <param name="spriteSheet">	Zbiór spriteów animacji. </param>
	/// <param name="keyFrames">  	Zbiór indeksów kolejnych klatek animacji. </param>
	/// <param name="duration">   	Czas trwania animacji w sekundach. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	FlipbookAnimation(std::shared_ptr<class SpriteSheet> spriteSheet, 
		const std::vector<std::uint32_t>& keyFrames, double duration);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	/// 	Funkcja tworząca animację z podanego zbioru spriteów oraz kolejnych klatek 
	/// 	animacji.  
	/// </summary>
	///
	/// <param name="spriteSheet">	Zbiór spriteów animacji. </param>
	/// <param name="keyFrames">  	Zbiór indeksów kolejnych klatek animacji. </param>
	/// <param name="duration">   	Czas trwania animacji w sekundach. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void create(std::shared_ptr<class SpriteSheet> spriteSheet,
		std::vector<std::uint32_t> keyFrames, double duration);

	/// <summary>	Destruktor. Nie robi nic szczególnego. </summary>
	~FlipbookAnimation();
	
	/// <summary>	Rozpoczyna animację zaczynając od aktualnej pozycji czasowej. </summary>
	void start(); 

	/// <summary>	
	/// 	Rozpoczyna animację wstecz o aktualnej pozycji czasowej lub jeśli wynosi ona 0
	/// 	od końca.
	/// </summary>
	void reverse();

	/// <summary>	Rozpoczyna animację od początku. </summary>
	void restart();

	/// <summary>	Ustawia pozycję czasową na 0 i zatrzymuje animację. </summary>
	void reset(); 

	/// <summary>	Zatrzymuje animację. </summary>
	void stop();

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja aktualizująca animację w czasie. </summary>
	///
	/// <param name="deltaTime">	Czas jaki upłynął od ostatniej aktualizacji. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void update(double deltaTime);

	///--------------------------------------------------------------------------------------------
	/// <summary>	Funkcja ustawiająca stan samoczynnego powtarzania animacji. </summary>
	///
	/// <param name="state">	Stan do ustawienia. </param>
	/// 
	///--------------------------------------------------------------------------------------------
	void setRepeat(bool state);

	///--------------------------------------------------------------------------------------------
	/// <summary>	
	/// 	Funkcja pobierająca wskaźnik do aktualnego sprite animacji bazując na aktualnej 
	/// 	klatce. 
	/// </summary>
	///
	/// <returns>	Aktualny sprite animacji </returns>
	/// 
	///--------------------------------------------------------------------------------------------
	std::weak_ptr<const class Sprite> getCurrentSprite() const;

private:
	/// <summary>	Indeksy kolejnych klatek animacji. </summary>
	std::vector<std::uint32_t> mKeyFramesIndices;
	/// <summary>	Wskaźnik na zbiór spriteów. </summary>
	std::shared_ptr<class SpriteSheet> mSpriteSheet;

	/// <summary>	Czas trwania animacji. </summary>
	double mDuration;
	/// <summary>	Aktualna pozycja czasowa. </summary>
	double mCurrentTime;
	/// <summary>	
	/// 	Kierunek odgrywania animacji. 
	/// 	Jeśli 1.0 - odgrywanie normalne. 
	/// 	Jeśli -1.0 - odgrywanie wsteczne
	/// </summary>
	double mPlayDirection;

	/// <summary>	Stan samoczynnego powtarzania animacji. </summary>
	bool mRepeat;
};

