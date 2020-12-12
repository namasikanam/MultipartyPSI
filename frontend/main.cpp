
#include <iostream>
#include "Network/BtChannel.h"
#include "Network/BtEndpoint.h"

using namespace std;
#include "Common/Defines.h"
using namespace osuCrypto;

#include "OtBinMain.h"
#include "bitPosition.h"

#include <numeric>
#include <fstream>
#include "Common/Log.h"
//int miraclTestMain();


void usage(const char* argv0)
{
	std::cout << "Error! Please use:" << std::endl;
	std::cout << "\t 1. For unit test: " << argv0 << " -u" << std::endl;
	std::cout << "\t 2. For simulation (3 parties <=> 3 machines): " << std::endl;;
	std::cout << "\t\t each machine: " << argv0 << " -n 3 -r 1 -m 36000 -p [pIdx] -i <input csv file>" << std::endl;
	std::cout << "\t\t The result table will be saved at data/result.csv at party 0." << std::endl;

}
int main(int argc, char** argv)
{

	//myCuckooTest_stash();
	//Table_Based_Random_Test();
	//OPPRF2_EmptrySet_Test_Main();
	//OPPRFn_EmptrySet_Test_Main();
	//Transpose_Test();
	//OPPRF3_EmptrySet_Test_Main();
	//OPPRFnt_EmptrySet_Test_Main();
	//OPPRFnt_EmptrySet_Test_Main();
	//OPPRFn_Aug_EmptrySet_Test_Impl();
	//OPPRFnt_EmptrySet_Test_Main();
	//OPPRF2_EmptrySet_Test_Main();
	//return 0;

	u64 trials = 1;
	u64 pSetSize = 5, psiSecParam = 40, bitSize = 128;

	u64 nParties, tParties, opt_basedOPPRF, setSize, isAug;

	u64 roundOPPRF;

	std::string infilename;

	switch (argc) {
	case 2: //unit test
		if (argv[1][0] == '-' && argv[1][1] == 'u')
			OPPRFnt_EmptrySet_Test_Main();
		break;

	case 7: //2PSI 
		if (argv[1][0] == '-' && argv[1][1] == 'n')
			nParties = atoi(argv[2]);
		else
		{
			usage(argv[0]);
			return 0;
		}

		if (argv[3][0] == '-' && argv[3][1] == 'm')
			setSize = 1 << atoi(argv[4]);
		else
		{
			usage(argv[0]);
			return 0;
		}

		if (argv[5][0] == '-' && argv[5][1] == 'p') {
			u64 pIdx = atoi(argv[6]);
			if (nParties == 2)
				party2(pIdx, setSize);
			else
			{
				usage(argv[0]);
				return 0;
			}
		}
		else
		{
			usage(argv[0]);
			return 0;
		}
		break;
	case 11: //nPSI or optimized 3PSI
		cout << "11\n";
		if (argv[1][0] == '-' && argv[1][1] == 'n')
			nParties = atoi(argv[2]);
		else
		{
			usage(argv[0]);
			return 0;
		}
		if (argv[3][0] == '-' && argv[3][1] == 'r' && nParties == 3)
		{
			roundOPPRF = atoi(argv[4]);
			tParties = 2;
		}
		else if (argv[3][0] == '-' && argv[3][1] == 't')
			tParties = atoi(argv[4]);

		else if (argv[3][0] == '-' && argv[3][1] == 'a')
			opt_basedOPPRF = atoi(argv[4]);

		else
		{
			usage(argv[0]);
			return 0;
		}

		if (argv[5][0] == '-' && argv[5][1] == 'm')
			setSize = atoi(argv[6]);
		else
		{
			usage(argv[0]);
			return 0;
		}

		if (argv[9][0] == '-' && argv[9][1] == 'i')
			infilename = std::string(argv[10]);
		else
		{
			usage(argv[0]);
			return 0;
		}

		if (argv[7][0] == '-' && argv[7][1] == 'p') {
			u64 pIdx = atoi(argv[8]);
			if (roundOPPRF == 1 && nParties == 3)
			{
				cout << nParties  << " " << roundOPPRF << " " << setSize << " " << pIdx << "\n";
				std::ifstream infile(infilename);
				party3(pIdx, setSize, trials, infile);
				infile.close();
			}
			else if (argv[3][1] == 't')
			{
				//cout << nParties << " " << tParties << " " << setSize << " " << pIdx << "\n";
				tparty(pIdx, nParties, tParties, setSize, trials);
			}
			else if (argv[3][1] == 'a')
			{
				aug_party(pIdx, nParties, setSize, opt_basedOPPRF, trials);
			}
		}
		else
		{
			usage(argv[0]);
			return 0;
		}

		break;
	}

	return 0;
}
