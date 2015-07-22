#include "decoder.h"
#include "io.h"
#include "basic_circuit.h"
#include "area.h"
#include "uca.h"
#include "parameter.h"
#include "cacti_interface.h"
#include "Ucache.h"
#include <iostream>
using namespace std;
#define endl '\n'
int main(int argc,char *argv[])
{
/*
  uca_org_t result;
  if (argc != 55)
  {
    bool infile_specified = false;
    string infile_name("");

    for (int32_t i = 0; i < argc; i++)
    {
      if (argv[i] == string("-infile"))
      {
        infile_specified = true;
        i++;
        infile_name = argv[i];
      }
    }

    if (infile_specified == false)
    {
      cerr << " Invalid arguments -- how to use CACTI:" << endl;
      cerr << "  1) cacti -infile <input file name>" << endl;
      cerr << "  2) cacti arg1 ... arg54 -- please refer to the README file" << endl;
      cerr << " No. of arguments input - " << argc << endl;
      exit(1);
    }
    else
    {
      result = cacti_interface(infile_name);
    }
  }
  else
  {
    result = cacti_interface(atoi(argv[ 1]),
                             atoi(argv[ 2]),
                             atoi(argv[ 3]),
                             atoi(argv[ 4]),
                             atoi(argv[ 5]),
                             atoi(argv[ 6]),
                             atoi(argv[ 7]),
                             atoi(argv[ 8]),
                             atof(argv[ 9]),
                             atoi(argv[10]),
                             atoi(argv[11]),
                             atoi(argv[12]),
                             atoi(argv[13]),
                             atoi(argv[14]),
                             atoi(argv[15]),
                             atoi(argv[16]),
                             atoi(argv[17]),
                             atoi(argv[18]),
                             atoi(argv[19]),
                             atoi(argv[20]),
                             atoi(argv[21]),
                             atoi(argv[22]),
                             atoi(argv[23]),
                             atoi(argv[24]),
                             atoi(argv[25]),
                             atoi(argv[26]),
                             atoi(argv[27]),
                             atoi(argv[28]),
                             atoi(argv[29]),
                             atoi(argv[30]),
                             atoi(argv[31]),
                             atoi(argv[32]),
                             atoi(argv[33]),
                             atoi(argv[34]),
                             atoi(argv[35]),
                             atoi(argv[36]),
                             atoi(argv[37]),
                             atoi(argv[38]),
                             atoi(argv[39]),
                             atoi(argv[40]),
                             atoi(argv[41]),
                             atoi(argv[42]),
                             atoi(argv[43]),
                             atoi(argv[44]),
                             atoi(argv[45]),
                             atoi(argv[46]),
                             atoi(argv[47]),
                             atoi(argv[48]),
                             atoi(argv[49]),
                             atoi(argv[50]),
                             atoi(argv[51]),
                             atoi(argv[52]),
                             atoi(argv[53]),
                             atoi(argv[54]));
  }
  int num_dec_signals = 256;
  double C_wl=15e-15;
  double R_wl=32000;
  bool is_fa=false;
  bool is_dram=false;
  Area cell;
  cell.set_w(1.04);
  cell.set_h(0.36);
  Decoder * row_dec = new Decoder(
      num_dec_signals,
      false,
      C_wl,
      R_wl,
      is_fa,
      is_dram,
      true,
      cell);
  cout << "number of gate is " << row_dec->num_gates << endl;
  double last_risetime=row_dec->compute_delays(0);
  for(int i=0; i<row_dec->num_gates;i++) {
    cout << "Width_N_" << i << "=\t\t" << row_dec->w_dec_n[i] << endl;
    cout << "Width_P_" << i << "=\t\t" << row_dec->w_dec_p[i] << endl;
    cout << "Stage[" << i << "]risetime=\t\t" << row_dec->tmp_risetime[i] << endl;
    cout << "Stage[" << i << "]delay=\t\t" << row_dec->tmp_delay[i] << endl;
    cout << "Stage[" << i << "]power=\t\t" << row_dec->tmp_power[i] << endl;
    cout << "last_risetime" << "=\t\t" << last_risetime <<endl;
  }
  cout << "Total delay = \t\t" << row_dec->delay << endl;
  cout << "Total power = \t\t" << row_dec->power.readOp.dynamic << endl;
  */
  //InputParameter * g_ip;
  g_ip=new InputParameter();
  g_ip->parse_cfg("cache.cfg");
  if(!g_ip->error_checking())
    cout<<"Error with configuration" <<endl;
  else {
    g_ip->display_ip();
  }
  //extern TechnologyParameter g_tp;
  init_tech_params(g_ip->F_sz_um,false);
  Wire winit;
  cout<<"pitch=" << g_tp.wire_local.pitch<<endl;
  cout<<"R_per_um="<< g_tp.wire_local.R_per_um <<", C_per_um="<<g_tp.wire_local.C_per_um<<endl;
    bool is_tag=false;
    int pure_ram=1;
    double Nspd=1;
    unsigned int Ndwl=4;
    unsigned int Ndbl=4;
    unsigned int Ndcm=8;
    unsigned int Ndsam_lev_1=1;
    unsigned int Ndsam_lev_2=1;
    bool is_main_mem=false;
  DynamicParameter dyn_p(is_tag, pure_ram, Nspd, Ndwl, Ndbl, Ndcm, Ndsam_lev_1, Ndsam_lev_2, is_main_mem);
  cout<<"cache size=" << g_ip->cache_sz<<endl;
  cout<<"number of banks=" << g_ip->nbanks<<endl;
  cout<<"block size=" << g_ip->block_sz<<endl;
  cout<<"associativity=" << g_ip->assoc<<endl;
  cout<<"Ndbl="<<dyn_p.Ndbl<<", Nspd="<<dyn_p.Nspd<<endl;
  cout<<"Number of rows in subarray is " << dyn_p.num_r_subarray << endl;
  cout<<"Number of columns in subarray is " << dyn_p.num_c_subarray << endl;
  if(dyn_p.is_valid)
    cout << "valid parameter" <<endl;
  else
    cout << "invalid parameter" <<endl;
  UCA * new_uca=new UCA(dyn_p);
  //cout<<"Wire cap of one row is " << new_uca->bank.mat.subarray.compute_C.C_b_metal << "F. Drain cap of one row is " << new_uca->bank.mat.subarray.C_b_row_drain_cap <<"F." <<endl;
  double C_gate_load=gate_C(1,0.0,false,true,false);
  cout<<"Gate cap per um(gate width) is " << C_gate_load <<endl;
  cout<<"Number of subarrays per mat is "<<dyn_p.num_subarrays/dyn_p.num_mats<<endl;
  cout<<"Number of rows in subarray is " <<  new_uca->bank.mat.subarray.num_rows<< endl;
  cout<<"Number of columns in subarray is " <<  new_uca->bank.mat.subarray.num_cols<< endl;
  cout<<"Number of output bits per mat is " << dyn_p.num_do_b_mat << endl;
  cout<<"Bitcell height is " << new_uca->bank.mat.subarray.cell.h << "um" <<endl;
  cout<<"Bitcell width is " << new_uca->bank.mat.subarray.cell.w << "um" <<endl;
  cout<<"BL wire cap of one row is " << new_uca->bank.mat.subarray.cell.h*g_tp.wire_local.C_per_um << "F" <<endl;
  cout<<"WL wire cap of one column is " << new_uca->bank.mat.subarray.cell.w*g_tp.wire_local.C_per_um << "F" <<endl;
  cout<<"Total bl cap of a subarray is " << new_uca->bank.mat.subarray.C_bl << endl;
  cout<<"Total wl cap of a subarray is " << new_uca->bank.mat.subarray.C_wl << endl;
  cout<<"BL diff voltage(SA sense voltage) is "<<dyn_p.V_b_sense <<endl;
  cout<<"BL delay is " << new_uca->bank.mat.delay_bitline << endl;
  cout<<"Dynamic read energy per mat is " << new_uca->bank.mat.power_bitline.readOp.dynamic <<endl;
  cout<<"Dynamic write energy per mat is " << new_uca->bank.mat.power_bitline.writeOp.dynamic <<endl;
  cout<<"BL precharge delay is " << new_uca->bank.mat.delay_bl_restore<<endl;
  cout<<"BL precharge energy per mat is " << new_uca->bank.mat.power_bl_precharge_eq_drv.readOp.dynamic<<endl;
  cout<<"SA delay is " << new_uca->bank.mat.delay_sa << endl;
  cout<<"Dynamic SA energy per mat is " << new_uca->bank.mat.power_sa.readOp.dynamic <<endl;
  cout<<"Row decoder delay is " << new_uca->bank.mat.row_dec->delay + new_uca->bank.mat.r_predec->delay<< endl;
  cout<<"Dynamic Row Decoders energy per mat is " << new_uca->bank.mat.power_row_decoders.readOp.dynamic <<endl;
  //The pre decoder is shared in one mat.
  cout<<"Dynamic Row pre-Decoders energy per mat is " << new_uca->bank.mat.r_predec->power.readOp.dynamic <<endl;
}
